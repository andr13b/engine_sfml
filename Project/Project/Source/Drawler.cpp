
#include "Drawler.h"

	Drawler::Drawler(sf::RenderWindow &w) : window(w)
	{

	}
	
	Drawler::~Drawler()
	{
	}


		void Drawler::clear()
		{

		}

		void Drawler::loadTexture(std::string name, std::string path, int countW, int countH)
		{
			sf::Image im;
			im.loadFromFile(path);
			sf::Texture tx;
			tx.loadFromImage(im);
			_Textures.push_back(tx);
			_names.push_back(name);		
			_paths.push_back(path);
			countOfSprites cs;
			cs.w = countW;
			cs.h = countH;
			_count.push_back(cs);
		}
		void Drawler::loadTextures_F(std::string filename, texter & tex)
		{
			_tex_list = tex.downloadFromFile_Vector(filename);
			int n = std::stoi(_tex_list[0]);
			for (int i = 1; i < _tex_list.size(); i += n)
			{
				// &sz
				loadTexture(_tex_list[i], _tex_list[i+1], std::stoi(_tex_list[i + 2]), std::stoi(_tex_list[i + 3]));
			}

		}
		void Drawler::DrawTexture(drawData dt, int wn, int hn)
		{
			sf::Sprite spr;
			spr.setPosition(dt._x, dt._y);
			spr.setRotation(dt._rot);
			float scaleX;
			float scaleY;

		for (int i = 0; i < _names.size(); i++)
		{
			if (_names[i] == dt._name)
			{
				spr.setTexture(_Textures[i]);
				int wh = spr.getTextureRect().width / _count[i].w;
				int hh = spr.getTextureRect().height / _count[i].h;
				spr.setTextureRect(sf::IntRect(0 * wh, 0 * hh, wh, hh));
				break;
			}
			if (i == _names.size() - 1)
			{
				int wh = spr.getTextureRect().width / _count[i].w;
				int hh = spr.getTextureRect().height / _count[i].h;
				spr.setTextureRect(sf::IntRect(0 * wh, 0 * hh, wh, hh));
				spr.setTexture(_Textures[i]);
			}
		}
		


		scaleX = dt._w / spr.getTextureRect().width;
		scaleY = dt._h / spr.getTextureRect().height;
		spr.setScale(scaleX, scaleY);
		window.draw(spr);
		}

		void Drawler::consoleinfo()
		{
			for each (std::string var in _names)
			{
				std::cout << var << " ";
			}
		}
