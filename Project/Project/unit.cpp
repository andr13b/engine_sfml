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

bool unit::isBusy()
{
	if (!path.empty() || ActiveGoal)return true;
	else return false;
}

void unit::setupChassey(float maxSpeed, float acceleration)
{
	leftTrack.setupTrack(maxSpeed, acceleration);
	rightTrack.setupTrack(maxSpeed, acceleration);
	distanceToStop = 0.5f*(maxSpeed + maxSpeed*maxSpeed / acceleration);
}

void unit::checkPath()
{
	if (!path.empty()&&!ActiveGoal)
	{
		order ord = path.front();
		typeState = ord._type;
		if (ord._type == "move" || ord._type == "rotate")
		{
			goalPAO = ord._pao;
			ActiveGoal = true;
		}
		path.pop_front();
	}
}

void unit::setGoalPath(std::list<order> orders)
{
	path = orders;
}

void unit::addGoalPath(std::list<order> orders)
{
	if (!orders.empty())path.insert(path.end(), orders.begin(), orders.end());
}

void unit::addGoalPath(order order)
{
	path.push_back(order);
}

void unit::clearGoalPath()
{
	path.clear();
}


void  unit::stopping()
{
	leftTrack.toStop();
	rightTrack.toStop();
}

void  unit::rotatingTo(float difOrient)
{
	//рекомендованные скорости для гусениц
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
	//рекомендованные скорости для гусениц
	float recSpeedL, recSpeedR;
	if (abs(difOrient) < GoalAngleDeviation)
	{
		recSpeedL = leftTrack.getMax();
		recSpeedR = rightTrack.getMax();
	}
	else
	{
		//"Нечеткий" доворот к цели по линейной функции
		//recSpeedR = (rightTrack.getMax())*(abs(difOrient)) / (180.0f);
		//recSpeedL = (leftTrack.getMax())*(abs(difOrient)) / (180.0f);
		//"Нечеткий" доворот к цели по корневой функции
		recSpeedR = (rightTrack.getMax())*sqrtf(abs(difOrient)) / sqrtf(180.0f);
		recSpeedL = (leftTrack.getMax())*sqrtf(abs(difOrient)) / sqrtf(180.0f);		
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

void unit::autoChassisToGoal(std::vector<unit> &units, discreteMap &dMap)
{
	sf::Vector2f vectorToGoal;//вектор до цели	
	sf::Vector2f vecRange;//вектор рассчета расстояний между элементами
	float range; // расстояние между двумя элементами
	float orientToGoal;//глобальный угол от положения юнита до цели
	//рекомендованные скорости для гусениц
	float recSpeedL, recSpeedR;
	float difOrient;//угол доворота к цели
	float distanceToGoal;//расстояние до цели
	float RD = GoalRadiusDeviation; //radius deviation - погрешность или допустимое расстояние

	if (typeState == "follow")
	{
		for (unit u : units)
		{
			if (u.num == num - 1)
			{
				goalPAO = u._pao;
				RD = followUnitRadius;
			}
			/*if (u.num < num)
			{
				vecRange = _pao.vec() - u._pao.vec();
				range = sqrtf(powf(vecRange.x, 2) + powf(vecRange.y, 2));
				if (range < influenceUnitRadius)
				{
					stopping();
					ActiveGoal = false;
					return;
				}
			}*/
		}
	}

	if (typeState == "move"|| typeState == "follow")
	{
		sf::Vector2i posInMap = dMap.cellNum(_pao.vec());//положение в дискретной карте
		sf::Vector2i posNear;//соседняя ячейка
		sf::Vector2f obsReject;//ветор отталкивания от препятствий
		obsReject.x = 0;
		obsReject.y = 0;
		//проверка на сближение с другими юнитами
		for (unit u : units)
			if (u.num < num) if (!u.isBusy() || u.getState() != "follow")
			{
				vecRange = _pao.vec() - u._pao.vec();
				range = sqrtf(powf(vecRange.x, 2) + powf(vecRange.y, 2));
				if (range < obstacleUnitRadius)
				{
					stopping();
					//ActiveGoal = false;
					return;
				}
			}
			else if (u.num != num)
			{
				vecRange = _pao.vec() - u._pao.vec();
				range = sqrtf(powf(vecRange.x, 2) + powf(vecRange.y, 2));
				if (range < influenceUnitRadius) obsReject += normalise(_pao.vec() - u._pao.vec());
			}		
		//расстояние до цели
		vectorToGoal = goalPAO.vec() - _pao.vec();	
		distanceToGoal = sqrtf(powf(vectorToGoal.x, 2) + powf(vectorToGoal.y, 2));
		//просмотр препятствий неподалеку		
		for (int i = -1; i <= 1; ++i)
			for (int j = -1; j <= 1; ++j) if (j != 0 || i != 0)
			{
				posNear.x = posInMap.x + i;
				posNear.y = posInMap.y + j;
				if (dMap.inBorders(posNear)) if (dMap._M[posNear.x][posNear.y] == 2)
				{
					obsReject += normalise(posInMap - posNear);
				}
			}
		vectorToGoal = normalise(vectorToGoal);
		vectorToGoal += obsReject;
		//выбор ориентации
		orientToGoal = toDegrees * atan2f(vectorToGoal.y, vectorToGoal.x);		
		difOrient = getDifAngle(_pao.orient, orientToGoal);
		
		if (distanceToGoal > RD)
		{
			movingTo(difOrient, distanceToGoal);
			ActiveGoal = true;
		}
		else
		{
			stopping();
			ActiveGoal = false;
		}
	}	
	if (typeState == "rotate")
	{
		difOrient = getDifAngle(_pao.orient, goalPAO.orient);
		if (abs(difOrient) > GoalAngleDeviation)
		{
			rotatingTo(difOrient);
			ActiveGoal = true;
		}
		else
		{			
			stopping();
			ActiveGoal = false;
		}
	}
	

	

}




void unit::tankTrackConvertSpeed()
{
	linearSpeed = (leftTrack.getSpeed() + rightTrack.getSpeed()) / 2.0f;
	angularSpeed = leftTrack.getSpeed() - rightTrack.getSpeed();
	rotate(angularSpeed);
	move(linearSpeed);
}

void unit::update(std::vector<unit> &units, discreteMap &dMap)
{	
	//checkPath();
	autoChassisToGoal(units, dMap);
	tankTrackConvertSpeed();
}

std::string unit::getState()
{
	return typeState;
}





/*
else
{
difOrient = getDifAngle(_pao.orient, goalPAO.orient);
if (abs(difOrient) > GoalAngleDeviation)
{
rotatingTo(difOrient);
}
else
{
isActiveGoal = false;
stopping();
}
}
*/



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


