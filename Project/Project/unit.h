#pragma once

#include "Source\TwodObj.h"
#include "Chassis.h"
#include "AStarSearch.h"

//константы 
#define GoalRadiusDeviation 15
#define GoalAngleDeviation 3

#define obstacleUnitRadius 50
#define influenceUnitRadius 30
#define followUnitRadius 80



//юнит - передвежная единица с гусеничным шасси
class unit : public TwodObj
{
private:
	//гусеничное шасси
	tankTrack leftTrack, rightTrack;	
	
	float linearSpeed;//линейная скорость в данный момент	
	float angularSpeed;//угловая скорость в данный момент
	
	//состояние или стратегия юнита
	std::string typeState;
	//команды на премещение, изменение состояний и тд
	std::list<order> path;
	
	//целевое положение и орентация
	PAO2d goalPAO;
	//есть цель перемещения
	bool ActiveGoal = false;
	//расстояние торможения
	float distanceToStop;
	
	//функции перемещения
	void stopping();
	void rotatingTo(float difOrient);
	void movingTo(float difOrient, float distanceToGoal);
	//автоуправление шасси 
	void autoChassisToGoal(std::vector<unit> &units, discreteMap &dMap);

	
	//перевод состояний гусениц в линейную и угловую скорость с дальнейшим перемещением
	void tankTrackConvertSpeed();

public:
	unit();
	unit(float w, float h, std::string _tex, Drawler &dr);
	~unit();

	int num;

	bool isBusy();
	std::string getState();
	//задание параметров гусеничного шасси
	void setupChassey(float maxSpeed, float acceleration);
	
	void setGoalPath(std::list<order> orders);
	void addGoalPath(std::list<order> orders);
	void addGoalPath(order order);
	void clearGoalPath();

	void checkPath();
	void update(std::vector<unit> &units, discreteMap &dMap);
	
	/*
	unit operator=(unit& inunit)
	{
		return *this;
	}
	*/
};




