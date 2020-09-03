#pragma once

#include "Source\TwodObj.h"
#include "Chassis.h"
#include "AStarSearch.h"

//��������� 
#define GoalRadiusDeviation 15
#define GoalAngleDeviation 3

#define obstacleUnitRadius 50
#define influenceUnitRadius 30
#define followUnitRadius 80



//���� - ����������� ������� � ���������� �����
class unit : public TwodObj
{
private:
	//���������� �����
	tankTrack leftTrack, rightTrack;	
	
	float linearSpeed;//�������� �������� � ������ ������	
	float angularSpeed;//������� �������� � ������ ������
	
	//��������� ��� ��������� �����
	std::string typeState;
	//������� �� ����������, ��������� ��������� � ��
	std::list<order> path;
	
	//������� ��������� � ���������
	PAO2d goalPAO;
	//���� ���� �����������
	bool ActiveGoal = false;
	//���������� ����������
	float distanceToStop;
	
	//������� �����������
	void stopping();
	void rotatingTo(float difOrient);
	void movingTo(float difOrient, float distanceToGoal);
	//�������������� ����� 
	void autoChassisToGoal(std::vector<unit> &units, discreteMap &dMap);

	
	//������� ��������� ������� � �������� � ������� �������� � ���������� ������������
	void tankTrackConvertSpeed();

public:
	unit();
	unit(float w, float h, std::string _tex, Drawler &dr);
	~unit();

	int num;

	bool isBusy();
	std::string getState();
	//������� ���������� ����������� �����
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




