#pragma once
#include "Drawler.h"
	
	//position and orientation - положение и ориентация 
	struct PAO2d
	{
		float x, y;
		float rot;
	};

	//д2 объект для отрисовки спрайта
	class TwodObj
	{
	private:
		float _w, _h;//длина и ширина объекта 
	protected:
		PAO2d _pao;//положение и ориентация		
		std::string _name = "";//название спрайта
	public:		
		 TwodObj();
		 TwodObj(std::string _tex, Drawler &dr);
		~TwodObj();

		float getX();
		float getY();
		float getRot();
		PAO2d getPAO();//положение и ориентация

		void setPic(std::string _tex, Drawler &dr);
		void setSize(float w, float h);

		void setCoord(float x, float y);
		void setAngle(float angle);

		void move(sf::Vector2f vector);//движение по вектору
		void move(float difX, float difY);//движение по каждой оси
		void move(float value);//движение сонаправлено ориентации

		void rotate(float defangle);
	
		void draw(Drawler &dr);
	};

