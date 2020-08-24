#include "keyboard.h"



keyboard::keyboard(sf::RenderWindow &w) : window(w)
{

}


keyboard::~keyboard()
{

}

void keyboard::keyboardFUNK()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window.close();
	}
	/*

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{


	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{

	}
	*/

#pragma region saves_loads
	//1
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
		{
			Windowselector = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) Windowselector = 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		changeSpeedSleep = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		{
			addspeed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) { addspeed = false; }
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt))
	{
		changeSpeedRobot = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		{
			addspeedRobot = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) { addspeedRobot = false; }
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
		{
			saveSlot1 = true;
		}
		else saveSlot1 = false;
	}
	else saveSlot1 = false;
	//down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
		{
			downSlot1 = true;
		}
		else downSlot1 = false;
	}
	else downSlot1 = false;
	//1
	//2
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
		{
			saveSlot2 = true;
		}
		else saveSlot2 = false;
	}
	else saveSlot2 = false;
	//down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
		{
			downSlot2 = true;
		}
		else downSlot2 = false;
	}
	else downSlot2 = false;
	//2
	//3
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
		{
			saveSlot3 = true;
		}
		else saveSlot3 = false;
	}
	else saveSlot3 = false;
	//down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
		{
			downSlot3 = true;
		}
		else downSlot3 = false;
	}
	else downSlot3 = false;
	//3
	//4
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
		{
			saveSlot4 = true;
		}
		else saveSlot4 = false;
	}
	else saveSlot4 = false;
	//down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
		{
			downSlot4 = true;
		}
		else downSlot4 = false;
	}
	else downSlot4 = false;
	//4
	//5
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
		{
			saveSlot5 = true;
		}
		else saveSlot5 = false;
	}
	else saveSlot5 = false;
	//down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
		{
			downSlot5 = true;
		}
		else downSlot5 = false;
	}
	else downSlot5 = false;
	//5
	//6
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
		{
			saveSlot6 = true;
		}
		else saveSlot6 = false;
	}
	else saveSlot6 = false;
	//down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
		{
			downSlot6 = true;
		}
		else downSlot6 = false;
	}
	else downSlot6 = false;
	//6
	//7
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))
		{
			saveSlot7 = true;
		}
		else saveSlot7 = false;
	}
	else saveSlot7 = false;
	//down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))
		{
			downSlot7 = true;
		}
		else downSlot7 = false;
	}
	else downSlot7 = false;
	//7
	//8
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
		{
			saveSlot8 = true;
		}
		else saveSlot8 = false;
	}
	else saveSlot8 = false;
	//down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
		{
			downSlot8 = true;
		}
		else downSlot8 = false;
	}
	else downSlot8 = false;
	//8
	//9
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))
		{
			saveSlot9 = true;
		}
		else saveSlot9 = false;
	}
	else saveSlot9 = false;
	//down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))
		{
			downSlot9 = true;
		}
		else downSlot9 = false;
	}
	else downSlot9 = false;
	//9
	//y-
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		minusY = true;
	}
	else minusY = false;
	//y+
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		plusY = true;
	}
	else plusY = false;
	//x+
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		plusX = true;
	}
	else plusX = false;
	//x-
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		minusX = true;
	}
	else minusX = false;
	//mouseL
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		mouseLab = true;
	}
	else mouseLab = false;
	//mouseB
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		mouseBase = true;
	}
	else mouseBase = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		simulation = true;
	}
	else simulation = false;
#pragma endregion 
	





}
