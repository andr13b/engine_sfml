#pragma once
#include "unitSquad.h"
#include <string>

/*
���������� �����, 
*/
struct discreteMap
{
	int **_M;//������ �����//0 - ��� ��������, 1 - ������, 2 - �����������
	sf::Vector2i _mapSize;//����������� ����� � �������
	sf::Vector2f _cellSize;//������ ������ ���������� �����
	//�������� ������ ���������� ����� ������������� ������� � �������� ����

	void init(sf::Vector2i mapSize, sf::Vector2u windowSize)
	{
		
	}
	bool initialyzed = false;
};


/*
�������, ����������� ���
*/
class world
{
private:	
	Drawler &dr;
	unitSquad us;//������ ������

	discreteMap dMap;//���������� �����

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

