#pragma once
#include <SFML/Graphics.hpp>


class keyboard
{
private:
	sf::RenderWindow &window;
public:
	//ya u mami programmist
#pragma region boolears
	bool saveSlot1 = false;
	bool saveSlot2 = false;
	bool saveSlot3 = false;
	bool saveSlot4 = false;
	bool saveSlot5 = false;
	bool saveSlot6 = false;
	bool saveSlot7 = false;
	bool saveSlot8 = false;
	bool saveSlot9 = false;
	bool downSlot1 = false;
	bool downSlot2 = false;
	bool downSlot3 = false;
	bool downSlot4 = false;
	bool downSlot5 = false;
	bool downSlot6 = false;
	bool downSlot7 = false;
	bool downSlot8 = false;
	bool downSlot9 = false;
	bool plusX = false;
	bool minusX = false;
	bool plusY = false;
	bool minusY = false;
	bool mouseLab = false;
	bool mouseBase = false;
	bool simulation = false;
	int Windowselector;
	bool changeSpeedSleep;
	bool addspeed;// для задержки
	bool changeSpeedRobot;
	bool addspeedRobot;
#pragma endregion stats for saves
	



	keyboard(sf::RenderWindow &w);
	~keyboard();
	void keyboardFUNK();
};

