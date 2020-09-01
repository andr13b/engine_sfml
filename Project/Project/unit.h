#pragma once

#include "Source\TwodObj.h"
#include "Chassis.h"
#include "AStarSearch.h"

//константы 
#define GoalRadiusDeviation 20 
#define GoalAngleDeviation 10



//юнит - передвежная единица с гусеничным шасси
class unit : public TwodObj
{
private:
	//гусеничное шасси
	tankTrack leftTrack, rightTrack;	
	
	float linearSpeed;//линейная скорость в данный момент	
	float angularSpeed;//угловая скорость в данный момент
	
	//целевое положение и орентация
	PAO2d goalPAO;
	



	//есть цель перемещения
	bool isActiveGoal = false;
	//расстояние торможения
	float distanceToStop;
	
	//функции перемещения
	void stopping();
	void rotatingTo(float difOrient);
	void movingTo(float difOrient, float distanceToGoal);
	//автоуправление шасси 
	void autoChassisToGoal();
	//перевод состояний гусениц в линейную и угловую скорость с дальнейшим перемещением
	void tankTrackConvertSpeed();

public:
	unit();
	unit(float w, float h, std::string _tex, Drawler &dr);
	~unit();	

	//задание параметров гусеничного шасси
	void setupChassey(float maxSpeed, float acceleration);

	//команды на премещение, изменение стратегии и тд
	std::list<order> orders;
	void checkForOrders();

	//задание целевых положения и ориентации
	void setGoalPAO(PAO2d pao);
	void update();

	
	unit operator=(unit& inunit)
	{
		return *this;
	}

};




