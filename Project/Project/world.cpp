#include "world.h"




world::world(Drawler &d) : dr(d)
{

}


world::~world()
{

}

void world::setup()
{
	PAO2d p;
	p.x = 500;
	p.y = 500;
	p.orient = 30;
	us.spawnUnitLine(7, p, 100, dr);
}

void world::loadDiscreteMap(std::string filename, sf::Vector2u winsize)
{
	std::vector<std::string> loadStr = T.downloadFromFile_Vector(filename);
	
	dMap._mapSize.y = atoi(loadStr[0].c_str());
	dMap._mapSize.x = loadStr.size() / dMap._mapSize.y;
	if (dMap.initialyzed)
	{
		for (int i = 0; i < dMap._mapSize.x; ++i)delete dMap._M[i];
		delete dMap._M;
	}
	dMap._cellSize.x = (float)winsize.x / (float)dMap._mapSize.x;
	dMap._cellSize.y = (float)winsize.y / (float)dMap._mapSize.y;
	dMap._M = new int*[dMap._mapSize.x];
	for (int i = 0; i < dMap._mapSize.x; ++i)
	{
		dMap._M[i] = new int[dMap._mapSize.y];
		//for (int j = 0; j < dMap._mapSize.x; ++j) dMap._M[i][j] = 0;
	}
	dMap.initialyzed = true;
	int z = 1;//����� ��������� �����
	//���������� �������� � ������
	for (int i = 0; i < dMap._mapSize.x; ++i)
		for (int j = 0; j < dMap._mapSize.y; ++j)
		{
			dMap._M[i][j] = atoi(loadStr[z].c_str());
			z++;
		}
	
}

void world::update(PAO2d goal)
{
	us.update(goal);
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

