#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "drawData.h"
#include "texter.h"
//std::vector<data>



	struct sizep
	{
		int w = 1;
		int h = 1;
	};



	class Drawler
	{
	private:
		std::vector<sf::Texture> _Textures;
		std::vector<std::string> _names;
		std::vector<std::string> _paths;
		std::vector<std::string> _tex_list;
		std::vector<sizep> _sizes;
		sf::RenderWindow &window;
	protected:
		
	public:		
		Drawler(sf::RenderWindow &w);
		~Drawler();
		void clear();
		void loadTexture(std::string name, std::string path, int countW, int countH);
		void loadTextures_F(std::string filename, texter &tex);
		std::vector<std::string> tex_list()
		{
			return _tex_list;
		}
		void DrawTexture(drawData dt);
		void drawLine(sf::Vector2f p1, sf::Vector2f p2, sf::Color color);
		void drawRectangle(sf::Vector2f pos, sf::Vector2f size, sf::Color color);

		void consoleinfo();
	};

