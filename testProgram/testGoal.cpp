#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<fstream>
#include<algorithm>
#include"Goal.h"
#include"myUtility.h"
#include"ScoreTime.h"

using namespace std;

int main(int argc, char** argv){
	vector<Goal> goals;

	// Readin "WorldCupEvents.csv", and need to do some data preprocessing before adding goal into goals.
	// As for an good coding style, we should not keep complicated logic in the application code main.cpp.
	// We should separate this concern to another file, and deal with preprocessing the input file to the format we needed separately.
	// Todo: for the purpose of seperating concerns, do the work mentioned right above.
	ifstream file2(argv[1]); // input file: ./data/WorldCupEvents.csv
	string line;
	getline(file2, line);
	while(getline(file2, line)){
		vector<string> tokens = str2Vec(line, ',');
		vector<string> eventVec = strSplit(tokens[tokens.size()-1], ' ');
		for(auto iter= eventVec.begin(); iter!=eventVec.end(); ++iter){
			string event = *iter;
			char gtype = event[0];
			if(gtype=='G'||gtype=='P'){ // if goal or penalty, we want to construct a Goal
				GoalType gt = (gtype=='G')?G:P;  // previous bug: GoalType= gtype; error illegal conversion from char to GoalType
				int gltime = stoi(event.substr(1, event.size()-2), nullptr, 10);
				int gmID = stoi(tokens[1], nullptr, 10);
	
				Goal goal = Goal(gmID, gltime, tokens[2], tokens[6], gt);
				goals.push_back(goal);
			}
		}
	}

	cout << "=========== Before sort ===========\n";
	for(auto iter = goals.begin(); iter!=goals.end(); ++iter){
		cout << *iter << endl;
	}

	sort(goals.begin(), goals.end(), ScoreTime());  //, ScoreTime() 
	cout << "=========== After sort by score time ===========\n";
	
	for(auto iter = goals.begin(); iter!=goals.end(); ++iter){
		cout << *iter << endl;
	}

	// vector<int> vec{32, 423, 3, 429, 4, 93, 44};
	// sort(vec.begin(), vec.end(), greater<int>());
	// for(auto iter = vec.begin(); iter!= vec.end(); ++iter) cout << *iter << ", ";        
}

