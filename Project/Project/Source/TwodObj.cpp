
#include "TwodObj.h"
#include "drawData.h"




	
TwodObj::TwodObj() 
{
}

TwodObj::TwodObj(float w, float h, std::string _tex, Drawler &dr)
{
	initImage(w, h, _tex, dr);
}

TwodObj::~TwodObj()
{

}

void TwodObj::initImage(float w, float h, std::string _tex, Drawler &dr)
{
	setPic(_tex, dr);
	setSize(w, h);
}
	
void TwodObj::setSize(float w, float h)
{
	_w = w;
	_h = h;
}

void TwodObj::setCoord(float x, float y)
{
	_pao.x = x;
	_pao.y = y;
}



float TwodObj::getX()
{
	return _pao.x;
}

float TwodObj::getY()
{
	return _pao.y;
}

float TwodObj::getRot()
{
	return _pao.y;
}

PAO2d TwodObj::getPAO()
{
	return _pao;
}

void TwodObj::setPic(std::string _tex, Drawler &dr)
{
	_name = _tex;
	std::vector<std::string> &list = dr.tex_list();
	bool default_tex = true;
	int n = std::stoi(list[0]);
	for (int i = 1; i < list.size(); i += n)
	{
		if (_name == list[i])
		{
			default_tex = false;
			break;
		}
	}
	if (default_tex)
	{
		_name = list[1];

	}

}

void TwodObj::move(sf::Vector2f vec)
{
	_pao.x += vec.x;
	_pao.y += vec.y;
}

void TwodObj::move(float difX, float difY)
{
	_pao.x += difX;
	_pao.y += difY;
}

void TwodObj::move(float value)
{
	_pao.x += value*cosf(_pao.orient * toRadian);
	_pao.y += value*sinf(_pao.orient * toRadian);
}

void TwodObj::setAngle(float angle)
{
	_pao.orient = angle;
}

void TwodObj::rotate(float defangle)
{
	_pao.orient += defangle;
	if (_pao.orient > 360)_pao.orient -= 360;
	if (_pao.orient < 0)_pao.orient += 360;
}


void TwodObj::draw(Drawler &dr)
{
	drawData dt; 
	//картинка привязана не к краю рамки, а к центру
	//вращение вокруг центра
	dt._x = _pao.x - sqrt(_w*_w + _h*_h)*cosf(_pao.orient* toRadian + atanf(_h / _w)) / 2.0f;
	dt._y = _pao.y - sqrt(_w*_w + _h*_h)*sinf(_pao.orient* toRadian + atanf(_h / _w)) / 2.0f;
	dt._rot = _pao.orient;
	dt._w = _w;
	dt._h = _h;
	dt._name = _name;
	dr.DrawTexture(dt);
}
