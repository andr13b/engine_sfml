#pragma once

#include "Source\TwodObj.h"
#include "Chassis.h"
#include "AStarSearch.h"

//��������� 
#define GoalRadiusDeviation 20 
#define GoalAngleDeviation 10



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
	void autoChassisToGoal();
	//������� ��������� ������� � �������� � ������� �������� � ���������� ������������
	void tankTrackConvertSpeed();

public:
	unit();
	unit(float w, float h, std::string _tex, Drawler &dr);
	~unit();	

	//������� ���������� ����������� �����
	void setupChassey(float maxSpeed, float acceleration);

	//������� �� ����������, ��������� ��������� � ��
	std::list<order> orders;
	void checkForOrders();

	//������� ������� ��������� � ����������
	void setGoalPAO(PAO2d pao);
	void update();

	
	unit operator=(unit& inunit)
	{
		return *this;
	}

};




