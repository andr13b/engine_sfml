
#include "TwodObj.h"
#include "drawData.h"

	
	
TwodObj::TwodObj() 
{
	_pao.rot = 0;
}


TwodObj::~TwodObj()
{

}

void TwodObj::initS(float x, float y, float scaleX, float scaleY)
{
	setCoord(x, y);
}

void TwodObj::initS(float x, float y, float scale)
{
	setCoord(x, y);
}
	
void TwodObj::initWH(float w, float h)
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
	std::vector<std::string> list = dr.tex_list();
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

void TwodObj::moveCoord(float defX, float defY)
{
	_pao.x += defX;
	_pao.y += defY;
}

void TwodObj::setAngle(float angle)
{
	_pao.rot = angle;
}

void TwodObj::rotate(float defangle)
{
	_pao.rot += defangle;
	if (_pao.rot > 360)_pao.rot -= 360;
	if (_pao.rot < 0)_pao.rot += 360;
}


void TwodObj::draw(Drawler &dr)
{
	drawData dt;
	dt._x = _pao.x - sqrt(_w*_w + _h*_h)*cos((_pao.rot + 57.29*atan(_h / _w)) / 57.29) / 2;
	dt._y = _pao.y - sqrt(_w*_w + _h*_h)*sin((_pao.rot + 57.29*atan(_h / _w)) / 57.29) / 2;
	dt._rot = _pao.rot;
	dt._w = _w;
	dt._h = _h;
	dt._name = _name;
	dr.DrawTexture(dt);
}
