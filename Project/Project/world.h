#pragma once

#include <string>
#include "unitSquad.h"




/*
объекты, наполн€ющие мир
*/
class world
{
private:	
	Drawler &dr;
	unitSquad us;//группа юнитов

	discreteMap dMap;//дискретна€ карта

	
	
	
	void drawMap();
	void loadDiscreteMap(std::string filename, sf::Vector2u winsize);//загрузка карты
	

public:
	
	world(Drawler &d);
	~world();
	/*
	
	
	*/
	void setup(std::string filename, sf::Vector2u winsize);
	

	/*
	итераци€ обновлени€ объектов мира
	*/
	void update();

	

	/*
	вывод на окно
	*/
	void draw();
};

