#include "unitSquad.h"



unitSquad::unitSquad()
{
}


unitSquad::~unitSquad()
{
}

void unitSquad::spawnUnitLine(int amoount, PAO2d leaderpao, float stepBetweenUnit, Drawler &dr)
{
	if (amoount > 0)
	{
		unit obj(30, 25, "tank_1", dr);
		obj.setCoord(leaderpao.x, leaderpao.y);
		obj.setAngle(leaderpao.orient);
		obj.setupChassey(3, 0.3);
		//первый юнит
		units.push_back(obj);
		sf::Vector2f stepVector; //вектор - шаг между юнитами
		stepVector.x = stepBetweenUnit * cosf((leaderpao.orient + 90.0f)*toRadian);
		stepVector.y = stepBetweenUnit * sinf((leaderpao.orient + 90.0f)*toRadian);
		int k;//направление шага // +1 или -1
		if (amoount > 1) for (int i = 1; i <= amoount; ++i)
		{
			if (i % 2 == 0) k = 1;
			else k = -1;
			leaderpao.x += stepVector.x*i*k;
			leaderpao.y += stepVector.y*i*k;
			obj.setCoord(leaderpao.x, leaderpao.y);
			units.push_back(obj);
		}
	}

}

void unitSquad::update(PAO2d goal)
{
	for (std::vector<unit>::iterator it = units.begin(); it != units.end(); ++it)
	{
		(*it).setGoalPAO(goal);
		(*it).update();
	}

}

void unitSquad::draw(Drawler &dr)
{
	for (unit u : units)
	{
		u.draw(dr);
	}
}
