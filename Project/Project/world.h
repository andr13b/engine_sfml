#pragma once
#include "unitSquad.h"
#include <string>

/*
дискретна€ карта, 
*/
struct discreteMap
{
	int **_M;//массив €чеек//0 - нет объектов, 1 - дорога, 2 - преп€тствие
	sf::Vector2i _mapSize;//размерность карты в €чейках
	sf::Vector2f _cellSize;//размер €чейки дискретной карты
	//создание пустой дискретной карты определенного размера в пределах окна

	void init(sf::Vector2i mapSize, sf::Vector2u windowSize)
	{
		
	}
	bool initialyzed = false;
};


/*
объекты, наполн€ющие мир
*/
class world
{
private:	
	Drawler &dr;
	unitSquad us;//группа юнитов

	discreteMap dMap;//дискретна€ карта

	texter T;
	
	void drawMap();

	

public:
	
	world(Drawler &d);
	~world();
	void setup();
	void loadDiscreteMap(std::string filename, sf::Vector2u winsize);

	void update(PAO2d goal);

	


	void draw();
};

