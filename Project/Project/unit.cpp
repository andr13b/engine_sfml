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




void unit::autoChasseyToGoal()
{
	if (isActiveGoal)
	{
		sf::Vector2f vectorToGoal = goalPAO.vec() - _pao.vec();//вектор до цели
		float orientToGoal = toDegrees * atan2f(vectorToGoal.y, vectorToGoal.x);//ориентация от юнита до цели
		if (orientToGoal < 0)orientToGoal += 360;
		float difOrient = orientToGoal - _pao.orient;//угол поворота юнита до цели
		if (difOrient < -180) difOrient += 360;
		if (difOrient > 180) difOrient -= 360;
		float distanceToGoal = sqrtf(powf(vectorToGoal.x, 2) + powf(vectorToGoal.y, 2));//расстояние до цели
		if (distanceToGoal > distanceToStop)
		{
			//рекомендованные скорости для гусениц
			float recSpeedL, recSpeedR;
			if (difOrient < 0)
			{
				recSpeedR = rightTrack.getMax()*(0.5f + 0.5f*(1 - abs(difOrient) / 180));
				recSpeedL = (leftTrack.getMax() - leftTrack.getMin())*((1 - abs(difOrient) / 180)) + leftTrack.getMin();
			}
			else
			{
				recSpeedL = leftTrack.getMax()*(0.5f + 0.5f*(1 - abs(difOrient) / 180));
				recSpeedR = (rightTrack.getMax() - rightTrack.getMin())*((1 - abs(difOrient) / 180)) + rightTrack.getMin();
			}


			if (recSpeedR > rightTrack.getSpeed())rightTrack.moreForward();
			else rightTrack.moreBack();
			if (recSpeedL > leftTrack.getSpeed())leftTrack.moreForward();
			else leftTrack.moreBack();
		}
		else
		{
			leftTrack.toStop();
			rightTrack.toStop();
		}
	}
	else
	{
		leftTrack.toStop();
		rightTrack.toStop();
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
