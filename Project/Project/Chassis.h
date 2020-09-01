#pragma once
#include <iostream>

//простейшая модель, соответствующая одной гусеницы 
class tankTrack
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
		currentSpeed += acceleration;
		if (currentSpeed > maxSpeed) currentSpeed = maxSpeed;
	}
	void moreBack()
	{
		currentSpeed -= acceleration;
		if (currentSpeed < minSpeed) currentSpeed = minSpeed;
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
