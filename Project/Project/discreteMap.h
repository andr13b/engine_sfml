#pragma once
/*
дискретна€ карта,
*/
struct discreteMap
{
	int **_M;//массив €чеек//0 - нет объектов, 1 - дорога, 2 - преп€тствие
	sf::Vector2i _mapSize;//размерность карты в €чейках
	sf::Vector2f _cellSize;//размер €чейки дискретной карты
	bool initialyzed = false;
	//получить номер €чейки по положению на экране
	sf::Vector2i cellNum(sf::Vector2f pixelPos)
	{
		sf::Vector2i CN;
		CN.x = pixelPos.x / _cellSize.x;
		CN.y = pixelPos.y / _cellSize.y;
		return CN;
	}
	//координаты цетра €чейки по еЄ номеру
	sf::Vector2f cellCentre(sf::Vector2i cellNum)
	{
		sf::Vector2f CC;
		CC.x = (0.5f + (float)cellNum.x)*_cellSize.x;
		CC.y = (0.5f + (float)cellNum.y)*_cellSize.y;
		return CC;
	}
	//индекс в пределах массива
	bool inBorders(sf::Vector2i index)
	{
		if (index.x >= 0 && index.y >= 0 && index.x < _mapSize.x || index.y < _mapSize.y)return true;
		return false;
	}


};




