#pragma once
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include "Source\TwodObj.h"
#include "discreteMap.h"

//������ ��� ��������� ���������, ��������� � ��.
struct order
{
	std::string _type;
	PAO2d _pao;
};

/*����*/
struct node
{
	sf::Vector2i index;
	std::string parentIndex;
	float costWay;//��������� ����
	float costFunc;//��������� 
};



/*
����� � ��������� ������� � ������� 
��������� A* - ����������� ��������� ��������
*/
class AStar
{
private:
	discreteMap &dMap;//���������� �����
	std::map<std::string, node> tree;//������ ������������� �����
	std::list<std::string> searchList;//������� �������� ����� ������, �� ������� ����� ��������� �����
	

	std::string vecToString(sf::Vector2i vec)
	{
		return std::to_string(vec.x) + " " + std::to_string(vec.y);
	}



public:
	AStar(discreteMap &d) : dMap(d){}
	~AStar() {}

	/*���������� ���� �� ������ rootCell �� goalCell
	canGrow - �������� ���������� �����, � ������� ����� ���� �����
	obstacle - �������� ���������� ����� - �����������
	*/
	std::list<order> searchPath(sf::Vector2i rootCell, sf::Vector2i goalCell, std::vector<int> canGrow, std::vector<int> obstacle)
	{
		tree.clear();
		searchList.clear();
		std::list<order> path;//����������� ����
		if (rootCell == goalCell)return path;
		//���� �� ��������� ���������� �����
		if (!dMap.inBorders(goalCell) || !dMap.inBorders(rootCell))return path;
		node n;//���� � ��������� ������ �������
		std::string index = vecToString(rootCell);//������ � ��������� ������ �������
		node nParent;//������������ ���� � ��������� ������ �������
		std::string parentIndex;//������������ ������ � ��������� ������ �������
		
		sf::Vector2i range;//���������� �� ���� � ������ �������
		
		//��������� ����		
		range = goalCell - rootCell;
		n.costWay = 0;
		n.costFunc = n.costWay + sqrtf(range.x * range.x + range.y * range.y);
		n.index = rootCell;
		n.parentIndex = "none";
		tree.insert(std::pair<std::string, node>(index, n));//��������� � ������
		searchList.push_back(index);//��������� � ������� ������������

		
		bool goalFound = false;//���� �������
		bool addedToList = false;//������ ������ �������� � ������� ������������

		bool additional = false;

		while (!searchList.empty() && !goalFound)
		{
			parentIndex = searchList.front();
			searchList.pop_front();

			nParent = tree[parentIndex];
			//+-1 �������� �����
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
									range = n.index - nParent.index;//���������� ����� ������
									n.costWay = nParent.costWay + sqrtf(range.x * range.x + range.y * range.y);
									range = goalCell - n.index;//���������� ����� ����� � �����
									n.costFunc = n.costWay + sqrtf(range.x * range.x + range.y * range.y);
									tree.insert(std::pair<std::string, node>(index, n));//��������� � ������
									addedToList = false;
									//���������� � ������� ������
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
									//�������� �� ������������ ����
									if (n.index == goalCell) goalFound = true;
								}
							}
				}
		}

		if (goalFound)
		{
			order o;//������ �� �����������
			sf::Vector2f pos;//��������� ��� ����������� � ��������
			//�������� �������� �������
			o._type = "move";
			o._pao.orient = 0;
			//��������� �����������
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




