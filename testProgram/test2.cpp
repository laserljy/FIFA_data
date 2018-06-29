// This is to test the class of WorldCup, including the c-tor


#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;

class WorldCup{
  private:
        int year;
        string country;
	string winner;
        // Team champion;
        // vector<string> teams;
        // vector<Game*> games;
  public:
        friend ostream& operator<< (ostream& os, const WorldCup wc){
		os << wc.year << ", "  << wc.country << ", and the winner is: " << wc.winner;
	       return os;	
	}
	
	WorldCup(string input):
		year(stoi(str2vec(input)[0], nullptr, 10)),
		country(str2vec(input)[1]),
		winner(str2vec(input)[2]) {}
	
	
	int getYear(void) const {return year;}
        string getCountry(void) const {return country;}
        string getWinner(void) const {return winner;}
        // void addGames(Game* game);
	
	vector<string> str2vec(string input){
		vector<string> result;
		istringstream iss(input);
		string token;
		while(getline(iss,token,',')){
			result.push_back(token);
		}
		return result;
	}

};

int main(int argc, char** argv){
	vector<WorldCup*> wcs;
	
	ifstream file = ifstream(argv[1]);
	string line;
	getline(file,line);
	while(getline(file,line)){
		wcs.push_back(new WorldCup(line));
	}

	for(auto itr=wcs.begin(); itr!=wcs.end(); ++itr){
		cout << **itr << endl;
	}
	
	for(auto itr = wcs.begin(); itr!=wcs.end(); ++itr){
		delete *itr;
	}
	// delete[] wcs;
}
