#pragma once
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include "Source\TwodObj.h"
#include "discreteMap.h"

//приказ для изменения поведения, положения и тд.
struct order
{
	std::string _type;
	PAO2d _pao;
};

/*узел*/
struct node
{
	sf::Vector2i index;
	std::string parentIndex;
	float costWay;//стоимость пути
	float costFunc;//стоимость 
};



/*
поиск в двумерном массиве с помощью 
алгоритма A* - модификации алгоритма Дейкстры
*/
class AStar
{
private:
	discreteMap &dMap;//дискретная карта
	std::map<std::string, node> tree;//дерево исследованных узлов
	std::list<std::string> searchList;//порядок индексов узлов дерева, по которым будет проходить поиск
	

	std::string vecToString(sf::Vector2i vec)
	{
		return std::to_string(vec.x) + " " + std::to_string(vec.y);
	}



public:
	AStar(discreteMap &d) : dMap(d){}
	~AStar() {}

	/*нахождение пути от ячейки rootCell до goalCell
	canGrow - значения дискретной карты, в которых может идти поиск
	obstacle - значения дискретной карты - препятствия
	*/
	std::list<order> searchPath(sf::Vector2i rootCell, sf::Vector2i goalCell, std::vector<int> canGrow, std::vector<int> obstacle)
	{
		tree.clear();
		searchList.clear();
		std::list<order> path;//построенный путь
		if (rootCell == goalCell)return path;
		//если за пределами дискретной карты
		if (!dMap.inBorders(goalCell) || !dMap.inBorders(rootCell))return path;
		node n;//узел в некоторый момент времени
		std::string index = vecToString(rootCell);//индекс в некоторый момент времени
		node nParent;//родительский узел в некоторый момент времени
		std::string parentIndex;//родительский индекс в некоторый момент времени
		
		sf::Vector2i range;//расстояние до цели в момент времени
		
		//стартовый узел		
		range = goalCell - rootCell;
		n.costWay = 0;
		n.costFunc = n.costWay + sqrtf(range.x * range.x + range.y * range.y);
		n.index = rootCell;
		n.parentIndex = "none";
		tree.insert(std::pair<std::string, node>(index, n));//добавляем в дерево
		searchList.push_back(index);//добавляем в очередь исследования

		
		bool goalFound = false;//цель найдена
		bool addedToList = false;//индекс ячейки добавлен в очередь исследования

		bool additional = false;

		while (!searchList.empty() && !goalFound)
		{
			parentIndex = searchList.front();
			searchList.pop_front();

			nParent = tree[parentIndex];
			//+-1 просмотр ячеек
			for (int i = -1; i <= 1 && !goalFound; ++i)
				for (int j = -1; j <= 1 && !goalFound; ++j) if (j != 0 || i != 0)
				{
					n.index.x = nParent.index.x + i;
					n.index.y = nParent.index.y + j;
					index = vecToString(n.index);
					if (dMap.inBorders(n.index))
						if (tree.find(index) == tree.end())
							if (std::find(canGrow.begin(), canGrow.end(), dMap._M[n.index.x][n.index.y]) != canGrow.end())
							{
								//additional part of algorythm
								additional = false;
								if (dMap.inBorders(sf::Vector2i(n.index.x + 1, n.index.y))) if (std::find(obstacle.begin(), obstacle.end(), dMap._M[n.index.x + 1][n.index.y]) != obstacle.end())additional = true;
								if (dMap.inBorders(sf::Vector2i(n.index.x - 1, n.index.y))) if (std::find(obstacle.begin(), obstacle.end(), dMap._M[n.index.x - 1][n.index.y]) != obstacle.end())additional = true;
								if (dMap.inBorders(sf::Vector2i(n.index.x, n.index.y + 1))) if (std::find(obstacle.begin(), obstacle.end(), dMap._M[n.index.x][n.index.y + 1]) != obstacle.end())additional = true;
								if (dMap.inBorders(sf::Vector2i(n.index.x, n.index.y - 1))) if (std::find(obstacle.begin(), obstacle.end(), dMap._M[n.index.x][n.index.y - 1]) != obstacle.end())additional = true;
								if (!additional)
								{
									n.parentIndex = parentIndex;
									range = n.index - nParent.index;//расстояние между узлами
									n.costWay = nParent.costWay + sqrtf(range.x * range.x + range.y * range.y);
									range = goalCell - n.index;//расстояние между узлом и целью
									n.costFunc = n.costWay + sqrtf(range.x * range.x + range.y * range.y);
									tree.insert(std::pair<std::string, node>(index, n));//добавляем в дерево
									addedToList = false;
									//добавление в очередь поиска
									for (std::list<std::string>::iterator it = searchList.begin(); it != searchList.end(); ++it)
									{
										if (n.costFunc < tree[(*it)].costFunc)
										{
											searchList.insert(it, index);
											addedToList = true;
											break;
										}
									}
									if (!addedToList) searchList.push_back(index);
									//проверка на соответствие цели
									if (n.index == goalCell) goalFound = true;
								}
							}
				}
		}

		if (goalFound)
		{
			order o;//приказ на перемещение
			sf::Vector2f pos;//положение для перемещения в пикселях
			//стандарт описания приказа
			o._type = "move";
			o._pao.orient = 0;
			//последнее перемещение
			index = vecToString(goalCell);
			n = tree[index];
			pos = dMap.cellCentre(n.index);
			o._pao.x = pos.x;
			o._pao.y = pos.y;
			path.push_front(o);
			index = n.parentIndex;
			while (index != "none")
			{				
				n = tree[index];
				pos = dMap.cellCentre(n.index);
				o._pao.x = pos.x;
				o._pao.y = pos.y;
				path.push_front(o);
				index = n.parentIndex;
			}
			
		}

		
		return path;
	}


};


/*
//map example
std::map<std::string, sf::Vector2i> asd;
sf::Vector2i v1;
sf::Vector2i v2;
std::string s1 = "20";
asd.insert(std::pair<std::string, sf::Vector2i>("hello", sf::Vector2i(10, 10)));
asd.insert(std::pair<std::string, sf::Vector2i>("a", sf::Vector2i(10, 10)));
asd.insert(std::pair<std::string, sf::Vector2i>("b", sf::Vector2i(10, 10)));
asd.insert(std::pair<std::string, sf::Vector2i>("c", sf::Vector2i(10, 10)));
if (asd.find("hellol") != asd.end())std::cout << "key found" << std::endl;
else std::cout << "key not found" << std::endl;
*/




