#include "world.h"



world::world(Drawler &d) : dr(d)
{

}


world::~world()
{
}

void world::spawnUnitLine(int amoount, PAO2d leaderpao, float stepBetweenUnit)
{
	if (amoount > 0)
	{
		unit obj(60, 50, "tank_1", dr);
		obj.setCoord(leaderpao.x, leaderpao.y);
		obj.setAngle(leaderpao.orient);
		obj.setupChassey(3, 0.3);
		//первый юнит
		unitSquad.push_back(obj);
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
			unitSquad.push_back(obj);
		}
	}

}

void world::update(PAO2d goal)
{
	for (std::vector<unit>::iterator it = unitSquad.begin(); it != unitSquad.end(); ++it)
	{
		(*it).setGoalPAO(goal);
		(*it).update();
	}

}

void world::draw()
{
	for (unit u : unitSquad)
	{
		u.draw(dr);
	}
}
