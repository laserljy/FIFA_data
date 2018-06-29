#include<iostream>
#include<sstream>
#include<fstream>
#include<map>
#include<string>
#include<vector>

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
	//
	// vector<string> inputVec;

  public:
	friend ostream& operator<< (ostream& os, const Game g){
		os << "Year: "<< g.year << ", gameID: " <<g.gameID << ", homeTeam: " << g.homeTeam << ", awayTeam: "  << g.awayTeam << ", scores: " << g.homeScore << ":" << g.awayScore;
		return os;
	}

	vector<string> str2Vec(string input){
		vector<string> result;
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
		homeTeam(inputVec[5]),
		awayTeam(inputVec[8]),
		homeScore(stoi(inputVec[6], nullptr, 10)),
		awayScore(stoi(inputVec[7], nullptr, 10)){}

	int getYear(void) const {return year;}
	bool isTie(void) const { return homeScore==awayScore;}
	string getWinner(void) const { 
		if(!isTie()) return (homeScore>awayScore)?homeTeam:awayTeam;
		else return "none";
	}
};

int main(int argc, char** argv){
	map<int, vector<Game*>> games;
	ifstream file(argv[1]);
	string line;
	getline(file, line);
	while(getline(file,line)){
		Game* game = new Game(line);
		int year = game->getYear();
		if(games.find(year)==games.end()) {
			games.insert(pair<int, vector<Game*>>(year,vector<Game*>(0)));
		}
		games[year].push_back(game);
	}
	int count;
	for(auto yearItr=games.begin(); yearItr!=games.end(); ++ yearItr){
		count = 0;
		int year = yearItr->first;
		auto allGames = yearItr->second;
		cout << "=========" << year << "=========" << endl; 
		
		for(auto gameItr=allGames.begin(); gameItr!=allGames.end(); ++gameItr){
			cout << **gameItr << endl;
			count++;
		}
		cout << "Total game for " << year << ": " << count << endl;
	}

	for(auto yearItr=games.begin(); yearItr!=games.end(); ++ yearItr){
		// int year = yearItr->first;
		auto allGames = yearItr->second;
		
		for(auto gameItr=allGames.begin(); gameItr!=allGames.end(); ++gameItr){
			delete *gameItr;
		}
	}
}
