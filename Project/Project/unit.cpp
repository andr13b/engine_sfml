#include "unit.h"



unit::unit()
{

}

unit::unit(float w, float h, std::string _tex, Drawler &dr)
{
	initImage(w, h, _tex, dr);
}


unit::~unit()
{

}

void unit::setupChassey(float maxSpeed, float acceleration)
{
	leftTrack.setupTrack(maxSpeed, acceleration);
	rightTrack.setupTrack(maxSpeed, acceleration);
	distanceToStop = 0.5f*(maxSpeed + maxSpeed*maxSpeed / acceleration);
}

void unit::setGoalPAO(PAO2d pao)
{
	isActiveGoal = true;
	goalPAO = pao;
}


void  unit::stopping()
{
	leftTrack.toStop();
	rightTrack.toStop();
}

void  unit::rotatingTo(float difOrient)
{
	//��������������� �������� ��� �������
	float recSpeedL, recSpeedR;
	recSpeedR = (rightTrack.getMax())*sqrtf(abs(difOrient)) / sqrtf(180.0f);
	recSpeedL = (leftTrack.getMax())*sqrtf(abs(difOrient)) / sqrtf(180.0f);
	if (difOrient < 0)recSpeedL *= -1.0f;
	else recSpeedR *= -1.0f;
	if (recSpeedR >= rightTrack.getSpeed()) rightTrack.moreForward();
	else rightTrack.moreBack();
	if (recSpeedL >= leftTrack.getSpeed()) leftTrack.moreForward();
	else leftTrack.moreBack();
}

void  unit::movingTo(float difOrient, float distanceToGoal)
{
	//��������������� �������� ��� �������
	float recSpeedL, recSpeedR;
	if (abs(difOrient) < GoalAngleDeviation)
	{
		recSpeedL = leftTrack.getMax();
		recSpeedR = rightTrack.getMax();
	}
	else
	{
		//"��������" ������� � ���� �� �������� �������
		//recSpeedR = (rightTrack.getMax())*(abs(difOrient)) / (180.0f);
		//recSpeedL = (leftTrack.getMax())*(abs(difOrient)) / (180.0f);
		//"��������" ������� � ���� �� �������� �������
		recSpeedR = (rightTrack.getMax())*sqrtf(abs(difOrient)) / sqrtf(180.0f);
		recSpeedL = (leftTrack.getMax())*sqrtf(abs(difOrient)) / sqrtf(180.0f);		
		if (difOrient < 0)recSpeedL *= -1.0f;
		else recSpeedR *= -1.0f;
		//���������� ��������
		float additionalSpeed;
		if (recSpeedR > 0)
		{
			additionalSpeed = rightTrack.getMax() - recSpeedR;
		}
		else
		{
			additionalSpeed = leftTrack.getMax() - recSpeedL;
		}
		//�������� ������ �� ���������� ��������
		recSpeedL += additionalSpeed;
		recSpeedR += additionalSpeed;
	}
	//����������, ���� ������ � ����
	if (distanceToGoal < distanceToStop)
	{
		recSpeedL *= (distanceToGoal / distanceToStop);
		recSpeedR *= (distanceToGoal / distanceToStop);
	}
	//������� �� �����
	if (recSpeedR >= rightTrack.getSpeed()) rightTrack.moreForward();
	else rightTrack.moreBack();
	if (recSpeedL >= leftTrack.getSpeed()) leftTrack.moreForward();
	else leftTrack.moreBack();
}

void unit::autoChasseyToGoal()
{
	if (isActiveGoal)
	{
		sf::Vector2f vectorToGoal = goalPAO.vec() - _pao.vec();//������ �� ����		
		float orientToGoal = toDegrees * atan2f(vectorToGoal.y, vectorToGoal.x);//���������� ���� �� ��������� ����� �� ����
		//��������������� �������� ��� �������
		float recSpeedL, recSpeedR;
		//���� �������� � ����
		float difOrient = getDifAngle(_pao.orient, orientToGoal);

		float distanceToGoal = sqrtf(powf(vectorToGoal.x, 2) + powf(vectorToGoal.y, 2));//���������� �� ����
		if (distanceToGoal > GoalRadiusDeviation)
		{
			movingTo(difOrient, distanceToGoal);
		}
		else
		{
			difOrient = getDifAngle(_pao.orient, goalPAO.orient);
			if (abs(difOrient) > GoalAngleDeviation)
			{
				rotatingTo(difOrient);
			}
			else
			{
				stopping();
			}
		}		
	}
	else
	{
		stopping();
	}
}

void unit::tankTrackConvertSpeed()
{
	linearSpeed = (leftTrack.getSpeed() + rightTrack.getSpeed()) / 2.0f;
	angularSpeed = leftTrack.getSpeed() - rightTrack.getSpeed();
	rotate(angularSpeed);
	move(linearSpeed);
}

void unit::update()
{	
	autoChasseyToGoal();
	tankTrackConvertSpeed();
}









/*float k = 1.0f;// 0.2f + 0.8f*distanceToGoal / distanceToStop;//����������� ���������� �� �������� � ����
if (difOrient < 0)
{
recSpeedR = rightTrack.getMax()*(0.5f + 0.5f*(1.0f - abs(difOrient) / 180.0f));
recSpeedL = (leftTrack.getMax() - leftTrack.getMin())*((1.0f - abs(difOrient) / 180.0f));
if (distanceToGoal < distanceToStop + 50.0f)recSpeedL *= (0.5f + 0.5f*distanceToGoal / (distanceToStop + 50.0f));
if (distanceToGoal < distanceToStop)
{
recSpeedL *= k;
recSpeedR *= k;
}
recSpeedL += leftTrack.getMin();
}
else
{
recSpeedL = leftTrack.getMax()*(0.5f + 0.5f*(1.0f - abs(difOrient) / 180.0f));
recSpeedR = (rightTrack.getMax() - rightTrack.getMin())*((1.0f - abs(difOrient) / 180.0f));
if (distanceToGoal < distanceToStop+50.0f)recSpeedR *= (0.5f + 0.5f*distanceToGoal / (distanceToStop + 50.0f));
if (distanceToGoal < distanceToStop)
{
recSpeedL *= k;
recSpeedR *= k;
}
recSpeedR += rightTrack.getMin();
}
*/


