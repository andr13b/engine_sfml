#pragma once
#include "Source\TwodObj.h"

struct tankTrack //параметры одной гусеницы 
{
private:
	float currentSpeed;//скорость на данный момент
	float maxSpeed;//граничная скорость вперед (положительное значение)
	float minSpeed;//граничная скорость назад (отрицательное значение)
	float acceleration;//ускорение
public:
	void setupTrack(float _maxSpeed, float _acceleration)
	{
		currentSpeed = 0;
		acceleration = _acceleration;
		maxSpeed = _maxSpeed;
		minSpeed = -_maxSpeed;
	}
	float getSpeed()
	{
		return currentSpeed;
	}
	float getMax()
	{
		return maxSpeed;
	}
	float getMin()
	{
		return minSpeed;
	}
	void moreForward()
	{
		if (currentSpeed < 0)toStop();
		else
		{
			currentSpeed += acceleration;
			if (currentSpeed > maxSpeed) currentSpeed = maxSpeed;
		}
	}
	void moreBack()
	{
		if (currentSpeed > 0)toStop();
		else
		{
			currentSpeed -= acceleration;
			if (currentSpeed < minSpeed) currentSpeed = minSpeed;
		}
	}
	void toStop()
	{
		if (currentSpeed > 0)
		{
			if (acceleration * 3 < currentSpeed) currentSpeed -= acceleration * 3;
			else currentSpeed = 0;
		}
		else if (currentSpeed < 0)
		{
			if (acceleration * 3 < abs(currentSpeed)) currentSpeed += acceleration * 3;
			else currentSpeed = 0;
		}
	}
};



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
	

	//автоуправление шасси 
	void autoChasseyToGoal();
	//перевод состояний гусениц в линейную и угловую скорость с дальнейшим перемещением
	void tankTrackConvertSpeed();

public:
	unit();
	unit(float w, float h, std::string _tex, Drawler &dr);
	~unit();	

	//задание параметров гусеничного шасси
	void setupChassey(float maxSpeed, float acceleration);
	//задание целевых положения и ориентации
	void setGoalPAO(PAO2d pao);
	

	

	void update();

};

