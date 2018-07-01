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
	int getGameID(void) const;
	int getGoalTime(void) const;
	string getTeamName(void) const;
	string getPlayer(void) const;
};


#endif // GOAL_H_
