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
		float orientToGoal = toDegrees * atan2f(vectorToGoal.y, vectorToGoal.x);//глобальный угол от положения юнита до цели
		if (orientToGoal < 0)orientToGoal += 360;
		float difOrient = orientToGoal - _pao.orient;//угол поворота юнита до цели
		if (difOrient < -180) difOrient += 360;
		else if (difOrient > 180) difOrient -= 360;
		float distanceToGoal = sqrtf(powf(vectorToGoal.x, 2) + powf(vectorToGoal.y, 2));//расстояние до цели
		if (distanceToGoal > GoalRadiusDeviation)
		{
			//рекомендованные скорости для гусениц
			float recSpeedL, recSpeedR;

			if (abs(difOrient) < GoalAngleDeviation)//5
			{
				recSpeedL = leftTrack.getMax();
				recSpeedR = rightTrack.getMax();
			}
			else
			{
				//"Нечеткий" доворот к цели по линейной функции
				//recSpeedR = (rightTrack.getMax())*(180.0f - (abs(difOrient))) / (180.0f);
				//recSpeedL = (leftTrack.getMax())*(180.0f - (abs(difOrient))) / (180.0f);
				//"Нечеткий" доворот к цели по корневой функции
				recSpeedR = (rightTrack.getMax())*sqrtf(180.0f - (abs(difOrient))) / sqrtf(180.0f);
				recSpeedL = (leftTrack.getMax())*sqrtf(180.0f - (abs(difOrient))) / sqrtf(180.0f);
				if (difOrient < 0)recSpeedL *= -1.0f;
				else recSpeedR *= -1.0f;
				//добавочная скорость
				float additionalSpeed;
				if (recSpeedR > 0)
				{
					additionalSpeed = rightTrack.getMax() - recSpeedR;
				}
				else
				{
					additionalSpeed = leftTrack.getMax() - recSpeedL;
				}
				//движение вперед на остаточную скорость
				recSpeedL += additionalSpeed;
				recSpeedR += additionalSpeed;
			}
			//замедление, если близко к цели
			if (distanceToGoal < distanceToStop)
			{
				recSpeedL *= (distanceToGoal / distanceToStop);
				recSpeedR *= (distanceToGoal / distanceToStop);
			}
			//команды на шасси
			if (recSpeedR >= rightTrack.getSpeed())rightTrack.moreForward();
			else rightTrack.moreBack();
			if (recSpeedL >= leftTrack.getSpeed())leftTrack.moreForward();
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









/*float k = 1.0f;// 0.2f + 0.8f*distanceToGoal / distanceToStop;//коэффициент замедления от близости к цели
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