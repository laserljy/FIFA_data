// Filename: test5.cpp
// This is an extend of test4.cpp to add goals to each game.
// input file: "WorldCupMatches.csv" and "WorldCupEvents.csv"

#include<iostream>
#include<sstream>
#include<fstream>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
#include"Goal.h"
#include"myUtility.h"
#include"ScoreTime.h"
//#include"GameID.h"

using namespace std;


class Game{
  private:
	vector<string> inputVec;  // initialization order is determined by definition order
	int year;
	int gameID;
	string homeTeam;
	string awayTeam;
	int homeScore;
	int awayScore;
	vector<Goal> goals;  // changed to map since I want all the goals sorted by time.
	
  public:
  	Game(){};
	Game(string input):
		inputVec(str2Vec(input, ',')),
		year(stoi(inputVec[0], nullptr, 10)),
		gameID(stoi(inputVec[17], nullptr, 10)),
		homeTeam(inputVec[18]),
		awayTeam(inputVec[19]),
		homeScore(stoi(inputVec[6], nullptr, 10)),
		awayScore(stoi(inputVec[7], nullptr, 10)){}

	int getYear(void) const {return year;}

	int getGameID(void) const {return gameID;}

	void addGoal(const Goal& goal) {
		goals.push_back(goal);
	}

	void sortGoals(void){
		sort(goals.begin(), goals.end(), ScoreTime());
	}

	bool anyGoal(void) const {return (homeScore+awayScore)>0;}

	// Todo: check goals.size()==(homeScore+awayScore);	

	bool isTie(void) { return homeScore==awayScore; }

	string winner(void) { 
		if(isTie()) return "none";
		else return (homeScore>awayScore)?homeTeam:awayTeam;
	}

	string firstGoaler(void) {
		return (goals[0]).getTeamName();
	}

	bool firstGoalerIsWinner(void) {
		string firstGoal = firstGoaler();
		string winTeam = winner();			// string winner= winner(); // error: no match to call .... YOU CANNOT use the same name for var and func
		if(winTeam.compare(firstGoal)==0)  
			return true;
		else return false;
	}

	void printAllGoals(void){
		for(auto it = goals.begin(); it!=goals.end(); ++it){
			cout << *it << ", ";
		}
		cout << endl;
	}

	friend ostream& operator<< (ostream& os, const Game& g){
		os << "Year: "<< g.year << ", gameID: " <<g.gameID << ", homeTeam: " << g.homeTeam << ", awayTeam: "  << g.awayTeam << ", scores: " << g.homeScore << ":" << g.awayScore;
		return os;
	}

	friend void addToMap (map<int, int>& gameID2Year, const Game& g){
		if(gameID2Year.find(g.gameID)==gameID2Year.end()) gameID2Year.insert(pair<int, int>(g.gameID, g.year));
	}
};

void addToMap(map<int, int>& gameID2Year, const Game& g);


class GameID{
public:
	GameID(int id): targetGameID(id){}
	bool operator()(const Game &game){
		return game.getGameID() == targetGameID;
	}

private:
	int targetGameID;
};


int main(int argc, char** argv){
	// build the map for games. <year, games in that year>
	map<int, vector<Game>> yearToGames;  // <yearOfWC, allTheGamesInThatWC>, this is actually the mini essential part of class WorldCup
	map<int, int> gameID2Year;
	ifstream file(argv[1]);
	string line;
	getline(file, line);
	while(getline(file,line)){
		Game game = Game(line);
		addToMap(gameID2Year, game);
		int year = game.getYear();
		if(yearToGames.find(year)==yearToGames.end()) {
			yearToGames.insert(pair<int, vector<Game>>(year,vector<Game>(0))); // error msg: test5.cpp:110:66:   required from here
                                                                               // /usr/lib/gcc/x86_64-pc-cygwin/6.4.0/include/c++/bits/stl_construct.h:75:7: error: no matching function for call to ‘Game::Game()’
																				// solved: define a c-tor with no param.
		}
		yearToGames[year].push_back(game);
	}

	// Print content in map gameID2Year to check.
	// for(auto iter = gameID2Year.begin(); iter!=gameID2Year.end(); ++iter){
	// 	cout << "GameID: " << iter->first << ", Year: " << iter->second << endl; 
	// }

	// ********** OK OK OK **********


	cout << "check point 0 \n";

	// Readin "WorldCupEvents.csv", and need to do some data preprocessing before adding goals.
	ifstream file2(argv[2]); // input file: ./data/WorldCupEvents.csv
	string line2;
	getline(file2, line2);
	while(getline(file2, line2)){
		vector<string> tokens = str2Vec(line2, ',');
		vector<string> eventVec = strSplit(tokens[tokens.size()-1], ' ');
		for(auto iter= eventVec.begin(); iter!=eventVec.end(); ++iter){
			string event = *iter;
			char gtype = event[0];
			if(gtype=='G'||gtype=='P'){ // if goal or penalty, we want to construct a Goal
				GoalType gltype = (gtype=='G')?G:P;
				int gltime = stoi(event.substr(1, event.size()-2), nullptr, 10);
				int gmID = stoi(tokens[1], nullptr, 10);
				Goal goal = Goal(gmID, gltime, tokens[2], tokens[6], gltype);
				
				int currGoalGameID = goal.getGameID();
				auto allGamesInWC = yearToGames[gameID2Year[currGoalGameID]];
				auto targetGame = find_if(allGamesInWC.begin(), allGamesInWC.end(), GameID(currGoalGameID));  
				// 3rd param: MatchingPredicate, lambda function: [](const Game& game)-> bool { return game.getGameID()==currGoalGameID; } , this is not correct..... functor GameID(currGoalGameID)
				if(targetGame!=allGamesInWC.end()) targetGame->addGoal(goal);
			}
		}
	}

	cout << "check point 10 \n";

	for(auto iter=yearToGames.begin(); iter!=yearToGames.end(); ++iter){
		cout << "check point 11 \n";
		int WCyear = iter->first;
		cout << "check point 12 \n";
		vector<Game> WC = iter->second;
		cout << "check point 13 \n";
		int gameWithGoalCount=0;
		int firstGoalerIsWinnerCount=0;
		for(auto gameIter = WC.begin(); gameIter!= WC.end(); ++gameIter){
			gameIter->sortGoals(); // it is sorted before call the firstGoal function


			cout << "check point 14 \n";
			cout << gameIter->anyGoal() << endl;
			gameIter->printAllGoals();  // nothing !!!!!!!!!STOP here, segmentation fault!!!!!
			
			cout << "Year: " << gameIter->getYear() << ", GameID: " << gameIter->getGameID() << endl ;
			if(gameIter->anyGoal()){
				cout << "check point 15 \n";
				gameWithGoalCount++;
				cout << "check point 15.1 \n";
				cout << "Year: " << gameIter->getYear() << ", GameID: " << gameIter->getGameID() << endl ;
				cout << "FirstGoalerIsWiner? Answer: " << gameIter->firstGoalerIsWinner();
				if(gameIter->firstGoalerIsWinner()){
					cout << "check point 16 \n";
					firstGoalerIsWinnerCount++;
				}
			}
		}
		double firstGoalerIsWinnerRatio = firstGoalerIsWinnerCount/gameWithGoalCount;
		cout << "In WC " << WCyear << ", the first goaler is winner ratio is: " << firstGoalerIsWinnerRatio;
	}


	// Delete dynamically allocated memory // I change to games from map<int, vector<*Game>> to map<int, vector<Game>>
	// Because dynamically allocated mem always need delete in the end. I construct goals using normal c-tor, so to
	// keep consistance, all the games should use normal c-tor as well
	// However using smart pointers will give the best of both methods, in case we prefer dynamically allocated objects.
	// for(auto yearItr=games.begin(); yearItr!=games.end(); ++ yearItr){
	// 	// int year = yearItr->first;
	// 	auto allGames = yearItr->second;
		
	// 	for(auto gameItr=allGames.begin(); gameItr!=allGames.end(); ++gameItr){
	// 		delete *gameItr;
	// 	}
	// }

}