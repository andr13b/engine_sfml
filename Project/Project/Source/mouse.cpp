#include "mouse.h"



mouse::mouse(sf::RenderWindow &w, mouseStater &ms) : window(w), MS(ms)
{
}


mouse::~mouse()
{
}

void mouse::mouseFunk()
{
	MS.x = sf::Mouse::getPosition().x - window.getPosition().x - 7;
	MS.y = sf::Mouse::getPosition().y - window.getPosition().y - 30;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		MS.lbDown = true;
	else MS.lbDown = false;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		MS.rbDown = true;
	else MS.rbDown = false;
	
}