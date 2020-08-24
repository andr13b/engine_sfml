#pragma once
#include <SFML/Graphics.hpp>



struct mouseStater
{
	int x = 0;
	int y = 0;
	bool rbDown = false;
	bool lbDown = false;
};


class mouse
{
private:
	sf::RenderWindow &window;
	
	
	
public:
	mouseStater &MS;
	mouse(sf::RenderWindow &w, mouseStater &ms);
	~mouse();
	void mouseFunk();
};

