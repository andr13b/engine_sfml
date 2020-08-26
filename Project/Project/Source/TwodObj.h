#pragma once
#include "Drawler.h"

#define toDegrees 57.2957f
#define toRadian 0.0174f

	
	//position and orientation - положение и ориентация 
	struct PAO2d
	{
		float x = 0;
		float y = 0;
		float orient = 0;
		sf::Vector2f vec()
		{
			sf::Vector2f nvec;
			nvec.x = x;
			nvec.y = y;
			return nvec;
		}
#pragma region operators
		PAO2d operator+=(const sf::Vector2f &term)
		{
			PAO2d npao = *this;
			return npao + term;
		}
		PAO2d operator+(const sf::Vector2f &term)
		{
			PAO2d npao = *this;
			npao.x = npao.x + term.x;
			npao.y = npao.y + term.y;
			return npao;
		}
		PAO2d operator-=(const sf::Vector2f &term)
		{
			PAO2d npao = *this;
			return npao - term;
		}
		PAO2d operator-(const sf::Vector2f &term)
		{
			PAO2d npao = *this;
			npao.x = npao.x - term.x;
			npao.y = npao.y - term.y;
			return npao;
		}
		
		PAO2d operator+=(const PAO2d &term)
		{
			PAO2d npao = *this;
			return npao + term;
		}
		PAO2d operator+(const PAO2d &term)
		{
			PAO2d npao = *this;
			npao.x = npao.x + term.x;
			npao.y = npao.y + term.y;
			npao.orient = npao.orient + term.orient;
			return npao;
		}
		PAO2d operator-=(const PAO2d &term)
		{
			PAO2d npao = *this;
			return npao - term;
		}
		PAO2d operator-(const PAO2d &term)
		{
			PAO2d npao = *this;
			npao.x = npao.x - term.x;
			npao.y = npao.y - term.y;
			npao.orient = npao.orient - term.orient;
			return npao;
		}
#pragma endregion
	};

	//объект для отрисовки спрайта и его перемещения по сцене
	class TwodObj
	{
	private:
		float _w, _h;//_w - ширина, _h - высота рамки заливки изображения
		std::string _name = "";//название спрайта
		void setPic(std::string _tex, Drawler &dr);
		void setSize(float w, float h);
	protected:
		PAO2d _pao;//положение и ориентация		
	public:		
		 TwodObj();
		 TwodObj(float w, float h, std::string _tex, Drawler &dr);
		~TwodObj();

		float getX();
		float getY();
		float getRot();
		//положение и ориентация
		PAO2d getPAO();

		//задать изображение и размеры рамки заливки
		void initImage(float w, float h, std::string _tex, Drawler &dr);

		//задание положения
		void setCoord(float x, float y);
		//задание ориентации в градусах
		void setAngle(float angle);

		//движение по вектору
		void move(sf::Vector2f vector);
		//движение по каждой оси
		void move(float difX, float difY);
		//движение сонаправлено ориентации
		void move(float value);
		//поворот на угол
		void rotate(float defangle);
	
		void draw(Drawler &dr);
	};

