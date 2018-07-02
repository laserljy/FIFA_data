#ifndef GOAL_H_
#define GOAL_H_
#include<string>

using namespace std;

enum GoalType {G, P};

class Goal{
  private:
	int gameID;
	int goalTime;
	string team;
	string player;
	GoalType typeOfGoal;
  public:
  	Goal(int gID, int gTime, string tm, string p, GoalType gt): 
  		gameID(gID), 
  		goalTime(gTime),
  		team(tm),
  		player(p),
  		typeOfGoal(gt){}
	
	friend ostream& operator<<(ostream& os, Goal& g){
		os << "GoalID: " << g.gameID << ", goalTime: " << g.goalTime << ", by " << g.player << " in " << g.team; 
		return os;
	}
	int getGameID(void) const {return gameID;}
	int getGoalTime(void) const {return goalTime;}
	string getTeamName(void) const {return team;}
	string getPlayer(void) const {return player;}
	GoalType getGoalType(void) const {return typeOfGoal;}
};


#endif // GOAL_H_
