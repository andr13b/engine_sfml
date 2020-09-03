#include "unitSquad.h"



unitSquad::unitSquad()
{
}


unitSquad::~unitSquad()
{
}


/*
создание линии юнитов
amount - количество
leaderpao - положение и ориентаци€ центрального юнита
stepBetweenUnit - рассто€ние между юнитами
*/
void unitSquad::spawnUnitLine(int amoount, PAO2d leaderpao, float stepBetweenUnit, Drawler &dr)
{
	if (amoount > 0)
	{
		unit obj(20, 16, "tank_1", dr);
		obj.setCoord(leaderpao.x, leaderpao.y);
		obj.setAngle(leaderpao.orient);
		obj.setupChassey(3, 0.3);
		obj.num = 0;
		//первый юнит
		units.push_back(obj);
		sf::Vector2f stepVector; //вектор - шаг между юнитами
		stepVector.x = stepBetweenUnit * cosf((leaderpao.orient + 90.0f)*toRadian);
		stepVector.y = stepBetweenUnit * sinf((leaderpao.orient + 90.0f)*toRadian);
		int k;//направление шага // +1 или -1
		if (amoount > 1) for (int i = 1; i < amoount; ++i)
		{
			if (i % 2 == 0) k = 1;
			else k = -1;
			leaderpao.x += stepVector.x*i*k;
			leaderpao.y += stepVector.y*i*k;
			obj.setCoord(leaderpao.x, leaderpao.y);
			obj.num = i;
			units.push_back(obj);
		}
	}
}

void unitSquad::setGoalPath(std::list<order> nOrders)
{
	orders = nOrders;
}

void unitSquad::addOrder(std::list<order> nOrders)
{
	orders.insert(orders.end(), nOrders.begin(), nOrders.end());
}

void unitSquad::addOrder(order nOrder)
{
	orders.push_back(nOrder);
}

void unitSquad::readOrders(discreteMap & dMap)
{
	for (unit u : units) if (u.isBusy())return;

	if (!orders.empty())
	{
		order ord = orders.front();
		std::vector<int> obstacleCells;
		std::vector<int> growCells;
		AStar AS(dMap);
		order uord;
		std::list<order> uorders;
		

		if (ord._type == "moveConvey")//движение в линии
		{
			growCells.push_back(0);
			growCells.push_back(1);
			obstacleCells.push_back(2);
			for (std::vector<unit>::iterator it = units.begin(); it != units.end(); ++it)
			{
				if (it == units.begin())
				{
					(*it).setGoalPath(AS.searchPath(dMap.cellNum((*it).getPAO().vec()), dMap.cellNum(ord._pao.vec()), growCells, obstacleCells));
				}
				else
				{
					uord._type = "follow";
					(*it).clearGoalPath();
					(*it).addGoalPath(uord);
				}
			}
		}
		else if (ord._type == "moveConveyR")//движение в линии по дороге
		{
			growCells.push_back(1);
			obstacleCells.push_back(2);
			for (std::vector<unit>::iterator it = units.begin(); it != units.end(); ++it)
			{
				if (it == units.begin())
					(*it).setGoalPath(AS.searchPath(dMap.cellNum((*it).getPAO().vec()), dMap.cellNum(ord._pao.vec()), growCells, obstacleCells));
				else
				{
					uord._type = "follow";
					(*it).clearGoalPath();
					(*it).addGoalPath(uord);
				}
			}
		}
		else if (ord._type == "runLine")//движение в линии по дороге
		{
			growCells.push_back(0);
			growCells.push_back(1);
			obstacleCells.push_back(2);
			PAO2d leaderpao = ord._pao;
			
			sf::Vector2f stepVector; //вектор - шаг между юнитами
			stepVector.x = ord.val * cosf((ord._pao.orient + 90.0f)*toRadian);
			stepVector.y = ord.val * sinf((ord._pao.orient + 90.0f)*toRadian);
			int k;//направление шага // +1 или -1
			int i = 0;
			for (std::vector<unit>::iterator it = units.begin(); it != units.end(); ++it)
			{
				(*it).clearGoalPath();
				if (i % 2 == 0) k = 1;
				else k = -1;
				leaderpao.x += stepVector.x*i*k;
				leaderpao.y += stepVector.y*i*k;
				//!!!!!!!!!//
				uorders = AS.searchPath(dMap.cellNum((*it).getPAO().vec()), dMap.cellNum(leaderpao.vec()), growCells, obstacleCells);		
				uord._pao = leaderpao;
				uord._type = "move";
				uorders.push_back(uord);
				(*it).setGoalPath(uorders);
				
				i++;
			}
		}		
		else if (ord._type == "rotate")
		{
			uord = ord;
			uorders.push_back(ord);
			for (std::vector<unit>::iterator it = units.begin(); it != units.end(); ++it)
			{
				(*it).clearGoalPath();
				
				(*it).setGoalPath(uorders);
			}
		}
		

		orders.pop_front();
	}

	/*
	std::vector<int> growCells;
	growCells.push_back(0);
	growCells.push_back(1);
	std::vector<int> obstacleCells;
	obstacleCells.push_back(2);
	AStar AS(dMap);
	
	for (std::vector<unit>::iterator it = units.begin(); it != units.end(); ++it)
	{
		(*it).setGoalPath(AS.searchPath(dMap.cellNum(sf::Vector2f((*it).getX(), (*it).getY())), sf::Vector2i(52, 22), growCells, obstacleCells));
	}
	growCells.clear();
	growCells.push_back(1);
	for (std::vector<unit>::iterator it = units.begin(); it != units.end(); ++it)
	{
		(*it).addGoalPath(AS.searchPath(sf::Vector2i(52, 22), sf::Vector2i(8, 22), growCells, obstacleCells));
	}
	growCells.push_back(0);
	for (std::vector<unit>::iterator it = units.begin(); it != units.end(); ++it)
	{
		(*it).addGoalPath(AS.searchPath(sf::Vector2i(8, 22), sf::Vector2i(16, 5), growCells, obstacleCells));
	}
	*/
}

void unitSquad::update(discreteMap &dMap)
{
	readOrders(dMap);
	for (std::vector<unit>::iterator it = units.begin(); it != units.end(); ++it) (*it).checkPath();
	for (std::vector<unit>::iterator it = units.begin(); it != units.end(); ++it) (*it).update(units, dMap);
}

void unitSquad::draw(Drawler &dr)
{
	for (unit u : units)
	{
		u.draw(dr);
	}
}
