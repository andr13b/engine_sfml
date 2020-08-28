#include <stdio.h>
#include <iostream>
#include <Windows.h>

#include <SFML/Graphics.hpp>

#include "Source/Drawler.h"
#include "Source/TwodObj.h"
#include "Source/keyboard.h"
#include "Source/mouse.h"
#include "unit.h"
#include "world.h"


#define myWindow 1920,1080
#define mouseInWindow M.MS.x > wPos.x - 15 && M.MS.x < wPos.x + wSize.x + 15 && M.MS.y > wPos.y - 15 && M.MS.y < wPos.y + wSize.y + 15




//sf::VideoMode(1600, 900), "Window"
//sf::VideoMode(SM_CXSCREEN, SM_CYSCREEN), "Window", sf::Style::Fullscreen
sf::RenderWindow window(sf::VideoMode(1600, 900), "Window"); 
sf::Vector2i wPos;//положение окна
sf::Vector2u wSize;//размер окна


keyboard K(window);
mouseStater MS;
mouse M(window, MS);


texter T;//зашрузчик файлов
Drawler dr(window);//рисовка объектов
TwodObj mouseObj;// объект отображения мыши


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
		wPos = window.getPosition();
		wSize = window.getSize();
		if (mouseInWindow)
		{
			if (MS.lbDown)
			{
				mouseObj.rotate(1);
			}
			if (MS.rbDown)
			{
				mouseObj.rotate(-1);
			}
		}
		mouseObj.setCoord(MS.x, MS.y);
		sf::sleep(sf::milliseconds(30));
	}
	
}


void setup()
{
	//Подгрузка иконки
	sf::Image im;
	im.loadFromFile("textures/def/defsmall.png");
	window.setIcon(im.getSize().x, im.getSize().y, im.getPixelsPtr());

	//Название окна
	window.setTitle("Unit_test");

	//изменить положение окна
	//sf::Vector2i winPos;
	//winPos.x = -10;
	//winPos.y = 0;
	//window.setPosition(winPos);

	FreeConsole();//закрыть консоль
	srand(time(0));//случайные числа без привязки к старту программы
	dr.loadTextures_F("Data/texture_list_1.dat", T);//загрузка списка спрайтов
	
	//замена картини мыши
	window.setMouseCursorVisible(false);//скрыть мышь
	mouseObj.initImage(80, 80, "mouse_1", dr);//выбор картинки
	mouseObj.setCoord(500, 500);//начальная координата


	



	/*
	//load font
	sf::Font font;//шрифт 
	font.loadFromFile("font/arial.ttf");//передаем нашему шрифту файл шрифта
	sf::Text text("", font, 50);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	text.setString("1:");//задает строку тексту
	text.setPosition(960, 12);//задаем позицию текста, центр камеры
	*/
}





int main()
{
	setup();

	//потоки на мышь и клавиатуру	
	sf::Thread threadK(&KEYBOARD_FUNK);
	threadK.launch();
	sf::Thread threadM(&MOUSE_FUNK);
	threadM.launch();	

	world wrld(dr);
	PAO2d p;
	p.x = 500;
	p.y = 500;
	p.orient = 30;
	wrld.spawnUnitLine(7, p, 100);

	//цикл отрисовки
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// кнопка "выход"
			if (event.type == sf::Event::Closed)
				window.close();			
		}

		
		wrld.update(mouseObj.getPAO());

		window.clear(sf::Color::White);
		wrld.draw();
		mouseObj.draw(dr);
		window.display();
		sf::sleep(sf::milliseconds(30));
	}	
	threadK.wait();
	threadM.wait();
	return EXIT_SUCCESS;
}