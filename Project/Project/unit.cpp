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
	//рекомендованные скорости дл€ гусениц
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
	//рекомендованные скорости дл€ гусениц
	float recSpeedL, recSpeedR;
	if (abs(difOrient) < GoalAngleDeviation)
	{
		recSpeedL = leftTrack.getMax();
		recSpeedR = rightTrack.getMax();
	}
	else
	{
		//"Ќечеткий" доворот к цели по линейной функции
		//recSpeedR = (rightTrack.getMax())*(abs(difOrient)) / (180.0f);
		//recSpeedL = (leftTrack.getMax())*(abs(difOrient)) / (180.0f);
		//"Ќечеткий" доворот к цели по корневой функции
		recSpeedR = (rightTrack.getMax())*sqrtf(abs(difOrient)) / sqrtf(180.0f);
		recSpeedL = (leftTrack.getMax())*sqrtf(abs(difOrient)) / sqrtf(180.0f);		
		if (difOrient < 0)recSpeedL *= -1.0f;
		else recSpeedR *= -1.0f;
		//добавочна€ скорость
		float additionalSpeed;
		if (recSpeedR > 0)
		{
			additionalSpeed = rightTrack.getMax() - recSpeedR;
		}
		else
		{
			additionalSpeed = leftTrack.getMax() - recSpeedL;
		}
		//движение вперед на добавочную скорость
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
	if (recSpeedR >= rightTrack.getSpeed()) rightTrack.moreForward();
	else rightTrack.moreBack();
	if (recSpeedL >= leftTrack.getSpeed()) leftTrack.moreForward();
	else leftTrack.moreBack();
}

void unit::autoChasseyToGoal()
{
	if (isActiveGoal)
	{
		sf::Vector2f vectorToGoal = goalPAO.vec() - _pao.vec();//вектор до цели		
		float orientToGoal = toDegrees * atan2f(vectorToGoal.y, vectorToGoal.x);//глобальный угол от положени€ юнита до цели
		//рекомендованные скорости дл€ гусениц
		float recSpeedL, recSpeedR;
		//угол доворота к цели
		float difOrient = getDifAngle(_pao.orient, orientToGoal);

		float distanceToGoal = sqrtf(powf(vectorToGoal.x, 2) + powf(vectorToGoal.y, 2));//рассто€ние до цели
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









/*float k = 1.0f;// 0.2f + 0.8f*distanceToGoal / distanceToStop;//коэффициент замедлени€ от близости к цели
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


