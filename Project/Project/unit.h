#pragma once
#include "Source\TwodObj.h"

//��������� 
#define GoalRadiusDeviation 20 
#define GoalAngleDeviation 10


//���������� ������, ��������������� ����� �������� 
class tankTrack
{
private:
	float currentSpeed;//�������� �� ������ ������
	float maxSpeed;//��������� �������� ������ (������������� ��������)
	float minSpeed;//��������� �������� ����� (������������� ��������)
	float acceleration;//���������

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



//���� - ����������� ������� � ���������� �����
class unit : public TwodObj
{
private:
	//���������� �����
	tankTrack leftTrack, rightTrack;	
	
	float linearSpeed;//�������� �������� � ������ ������	
	float angularSpeed;//������� �������� � ������ ������
	
	//������� ��������� � ���������
	PAO2d goalPAO;


	//���� ���� �����������
	bool isActiveGoal = false;
	//���������� ����������
	float distanceToStop;
	
	//������� �����������
	void stopping();
	void rotatingTo(float difOrient);
	void movingTo(float difOrient, float distanceToGoal);
	//�������������� ����� 
	void autoChasseyToGoal();
	//������� ��������� ������� � �������� � ������� �������� � ���������� ������������
	void tankTrackConvertSpeed();

public:
	unit();
	unit(float w, float h, std::string _tex, Drawler &dr);
	~unit();	

	//������� ���������� ����������� �����
	void setupChassey(float maxSpeed, float acceleration);
	//������� ������� ��������� � ����������
	void setGoalPAO(PAO2d pao);
	

	

	void update();

	
	unit operator=(unit& inunit)
	{
		return *this;
	}

};




