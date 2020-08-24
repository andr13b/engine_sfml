#include <stdio.h>
#include <iostream>
#include <Windows.h>

#include <SFML/Graphics.hpp>

#include "Source/Drawler.h"
#include "Source/TwodObj.h"
#include "Source/keyboard.h"
#include "Source/mouse.h"



#define myWindow 1920,1080
#define mouseInWindow M.MS.x > window.getPosition().x - 15 && M.MS.x<window.getPosition().x + window.getSize().x + 15 && M.MS.y > window.getPosition().y - 15 && M.MS.y < window.getPosition().y + window.getSize().y + 15




//sf::VideoMode(1600, 900), "Window"
//sf::VideoMode(SM_CXSCREEN, SM_CYSCREEN), "Window", sf::Style::Fullscreen
sf::RenderWindow window(sf::VideoMode(1600, 900), "Window");


keyboard K(window);
mouseStater MS;
mouse M(window, MS);


texter T;//��������� ������
Drawler dr(window);//������� ��������
TwodObj ob;//����





void KEYBOARD_FUNK()
{
	while (window.isOpen())
	{
		K.keyboardFUNK();
		sf::sleep(sf::milliseconds(30));
	}
}

void MOUSE_FUNK()
{
	while (window.isOpen())
	{
		M.mouseFunk();
		if (mouseInWindow)
		{
			if (MS.lbDown)
			{
				ob.rot(1);
			}
			if (MS.rbDown)
			{
				ob.rot(-1);
			}
		}
		ob.setCoord(MS.x, MS.y);
		sf::sleep(sf::milliseconds(30));
	}
	
}


void setup()
{
	//��������� ������
	sf::Image im;
	im.loadFromFile("textures/def/defsmall.png");
	window.setIcon(im.getSize().x, im.getSize().y, im.getPixelsPtr());

	//�������� ����
	window.setTitle("Unit_test");

	//�������� ��������� ����
	//sf::Vector2i winPos;
	//winPos.x = -10;
	//winPos.y = 0;
	//window.setPosition(winPos);

	FreeConsole();//������� �������
	srand(time(0));//��������� ����� ��� �������� � ������ ���������
	dr.loadTextures_F("Data/texture_list_1.dat", T);//�������� ������ ��������
	
	//������ ������� ����
	window.setMouseCursorVisible(false);//������ ����
	ob.setPic("mouse_1", dr);//����� ��������
	ob.setCoord(500, 500);//��������� ����������
	ob.initWH(80, 80);//������ ����

	/*
	//load font
	sf::Font font;//����� 
	font.loadFromFile("font/arial.ttf");//�������� ������ ������ ���� ������
	sf::Text text("", font, 50);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	text.setString("1:");//������ ������ ������
	text.setPosition(960, 12);//������ ������� ������, ����� ������
	*/
}





int main()
{
	setup();

	//������ �� ���� � ����������	
	sf::Thread threadK(&KEYBOARD_FUNK);
	threadK.launch();
	sf::Thread threadM(&MOUSE_FUNK);
	threadM.launch();	

	
	




	//���� ���������
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// ������ "�����"
			if (event.type == sf::Event::Closed)
				window.close();
		}
		

		window.clear(sf::Color::White);
		ob.draw(dr);
		window.display();
		sf::sleep(sf::milliseconds(30));
	}	
	return EXIT_SUCCESS;
}