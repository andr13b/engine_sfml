#include "world.h"




world::world(Drawler &d) : dr(d)
{

}


world::~world()
{

}

void world::setup(std::string filename, sf::Vector2u winsize)
{
	//�������� ����� 
	loadDiscreteMap(filename, winsize);
	//����� ��������
	PAO2d p;
	p.x = 1350;
	p.y = 120;
	p.orient = 90;
	us.spawnUnitLine(3, p, 55, dr);
	//���������� �����
	order ord;
	ord._pao.orient = -90;
	ord._type = "moveConvey";
	ord._pao.x = 1390;
	ord._pao.y = 600;
	us.addOrder(ord);
	ord._type = "moveConveyR";
	ord._pao.x = 220;
	ord._pao.y = 600;
	us.addOrder(ord);
	ord._type = "runLine";
	ord.val = 100;
	ord._pao.orient = -90;
	ord._pao.x = 430;
	ord._pao.y = 140;
	us.addOrder(ord);
	ord._type = "rotate";
	ord._pao.orient = -90;
	ord._pao.x = 430;
	ord._pao.y = 140;
	us.addOrder(ord);

	

}

void world::loadDiscreteMap(std::string filename, sf::Vector2u winsize)
{	
	if (dMap.initialyzed)
	{
		for (int i = 0; i < dMap._mapSize.x; ++i)delete dMap._M[i];
		delete dMap._M;
	}
	//�������� �����
	texter T;
	std::vector<std::string> loadStr = T.downloadFromFile_Vector(filename);
	//����������� ���������� �����
	dMap._mapSize.x = atoi(loadStr[0].c_str());
	dMap._mapSize.y = loadStr.size() / dMap._mapSize.x;	
	dMap._cellSize.x = (float)winsize.x / (float)dMap._mapSize.x;
	dMap._cellSize.y = (float)winsize.y / (float)dMap._mapSize.y;
	//��������� ������
	dMap._M = new int*[dMap._mapSize.x];
	for (int i = 0; i < dMap._mapSize.x; ++i)
	{
		dMap._M[i] = new int[dMap._mapSize.y];
		for (int j = 0; j < dMap._mapSize.y; ++j) dMap._M[i][j] = 0;
	}
	dMap.initialyzed = true;
	int z = 1;//����� ��������� �����
	//���������� �������� � ������
	for (int j = 0; j < dMap._mapSize.y; ++j)
		for (int i = 0; i < dMap._mapSize.x; ++i)		
		{
			dMap._M[i][j] = atoi(loadStr[z].c_str());
			z++;
		}	
}

void world::update()
{
	us.update(dMap);
}



void world::drawMap()
{
	for (int i = 0; i < dMap._mapSize.x; ++i)
		for (int j = 0; j < dMap._mapSize.y; ++j)
		{
			switch (dMap._M[i][j])
			{
			case 1:
				dr.drawRectangle(sf::Vector2f(dMap._cellSize.x*i, dMap._cellSize.y*j), dMap._cellSize, sf::Color::Green);
				break;
			case 2:
				dr.drawRectangle(sf::Vector2f(dMap._cellSize.x*i, dMap._cellSize.y*j), dMap._cellSize, sf::Color::Black);
				break;
			default:
				break;
			}
		}
}

void world::draw()
{
	if (dMap.initialyzed)drawMap();
	us.draw(dr);
}

