#pragma once
#include <SFML/Graphics.hpp>
#include "Source/TwodObj.h"

class button
{
private:
	sf::RenderWindow &w;
	TwodObj &TWD;
	std::string _originalName;
	std::string _mouseUpName;
	std::string _mouseDownName;



public:
	void checkButton();
	button(sf::RenderWindow &window, TwodObj &twodObj);
	~button();
};

