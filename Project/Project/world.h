#pragma once

#include <string>
#include "unitSquad.h"




/*
�������, ����������� ���
*/
class world
{
private:	
	Drawler &dr;
	unitSquad us;//������ ������

	discreteMap dMap;//���������� �����

	
	
	
	void drawMap();
	void loadDiscreteMap(std::string filename, sf::Vector2u winsize);//�������� �����
	

public:
	
	world(Drawler &d);
	~world();
	/*
	
	
	*/
	void setup(std::string filename, sf::Vector2u winsize);
	

	/*
	�������� ���������� �������� ����
	*/
	void update();

	

	/*
	����� �� ����
	*/
	void draw();
};

