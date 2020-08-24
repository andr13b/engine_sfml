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
		float _w, _h;//длина и ширина изображения
	protected:
		PAO2d _pao;//положение и ориентация		
		std::string _name = "";//название спрайта
	public:		
		 TwodObj();
		~TwodObj();

		float getX();
		float getY();
		float getRot();
		PAO2d getPAO();//положение и ориентация

		void initS(float x, float y, float scaleX, float scaleY);
		void initS(float x, float y, float scale);
		void initWH(float w, float h);
		void setCoord(float x, float y);

		void setPic(std::string _tex, Drawler &dr);
		void moveCoord(float defX, float defY);
		void setAngle(float angle);
		void rotate(float defangle);
		void draw(Drawler &dr);
	};

