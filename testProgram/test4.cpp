// Filename: test4.cpp
// This is an extend of test3.cpp to incorperate all the goals in the member data goals.
// input file: WorldCupMatches.csv, and WorldCupPlayer_test

#include<iostream>
#include<sstream>
#include<fstream>
#include<map>
#include<string>
#include<vector>

#include"Goal.h"

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
	// vector<Goal*> goals;

  public:
	friend ostream& operator<< (ostream& os, const Game& g){
		os << "Year: "<< g.year << ", gameID: " <<g.gameID << ", homeTeam: " << g.homeTeam << ", awayTeam: "  << g.awayTeam << ", scores: " << g.homeScore << ":" << g.awayScore;
		return os;
	}

	friend void addToMap (map<int, int>& gameID2Year, const Game& g){
		if(gameID2Year.find(g.gameID)==gameID2Year.end()) gameID2Year.insert(pair<int, int>(g.gameID, g.year));
	}

	// friend void print(const Game& g){
	// 	cout << "Game year: " << g.year << endl;
	// }

	vector<string> str2Vec(string input){
		vector<string> result;
		// A bug was found when trying to use country name abbreviation instead of full name. Then the print out formation is quite confusing, after trying different elements, I finally identitified that it is because we access the last elem in the vector.
		// this is the OS dependent thing, in Windows there two chars at the end of line: \r\n, that is why unexpected things happen when accessing the last elem in the inputVec, need to get rid of the last char. See this link: http://www.cplusplus.com/forum/general/51349/, comments by mik2718
		input = input.substr(0, input.size()-1);
		istringstream iss(input);
		string token;
		while(getline(iss, token, ',')){
			result.push_back(token);
		}
		return result;
	}

	Game(string input):
		inputVec(str2Vec(input)),
		year(stoi(inputVec[0], nullptr, 10)),
		gameID(stoi(inputVec[17], nullptr, 10)),
		homeTeam(inputVec[18]),
		awayTeam(inputVec[19]),
		homeScore(stoi(inputVec[6], nullptr, 10)),
		awayScore(stoi(inputVec[7], nullptr, 10)){}

	int getYear(void) const {return year;}
	bool isTie(void) const { return homeScore==awayScore;}
	string getWinner(void) const { 
		if(!isTie()) return (homeScore>awayScore)?homeTeam:awayTeam;
		else return "none";
	}
};

// void print(const Game& g);
void addToMap(map<int, int>& gameID2Year, const Game& g);

int main(int argc, char** argv){
	// build the map for games. <year, games in that year>
	map<int, vector<Game*>> games;
	map<int, int> gameID2Year;
	ifstream file(argv[1]);
	string line;
	getline(file, line);
	while(getline(file,line)){
		Game* game = new Game(line);
		addToMap(gameID2Year, *game);
		//print(*game);
		int year = game->getYear();
		if(games.find(year)==games.end()) {
			games.insert(pair<int, vector<Game*>>(year,vector<Game*>(0)));
		}
		games[year].push_back(game);
	}

	// Print games to check.
	// int count;
	// for(auto yearItr=games.begin(); yearItr!=games.end(); ++ yearItr){
	// 	count = 0;
	// 	int year = yearItr->first;
	// 	auto allGames = yearItr->second;
	// 	cout << "=========" << year << "=========" << endl; 
		
	// 	for(auto gameItr=allGames.begin(); gameItr!=allGames.end(); ++gameItr){
	// 		cout << **gameItr << endl;
	// 		count++;
	// 	}
	// 	cout << "Total game for " << year << ": " << count << endl;
	// }

	// ============

	// Print gameID2Year to check.
	for(auto iter = gameID2Year.begin(); iter!=gameID2Year.end(); ++iter){
		cout << "GameID: " << iter->first << ", Year: " << iter->second << endl; 
	}


	for(auto yearItr=games.begin(); yearItr!=games.end(); ++ yearItr){
		// int year = yearItr->first;
		auto allGames = yearItr->second;
		
		for(auto gameItr=allGames.begin(); gameItr!=allGames.end(); ++gameItr){
			delete *gameItr;
		}
	}
}
