
#include "texter.h"

using namespace std;


	texter::texter()
	{

	}
	
	texter::~texter()
	{

	}

	void texter::uploadToFile(std::string fileName, std::string value)
	{
		_ofstr.open(fileName);
		_ofstr << value;
		_ofstr.close();
	}

	void texter::uploadToFile(std::string fileName, char * value)
	{
		_ofstr.open(fileName);
		_ofstr << value;
		_ofstr.close();
	}
	
	void texter::uploadToFile(std::string fileName, float value) {}

	void texter::addToFile(std::string fileName, std::string value)
	{
		std::vector<std::string> s;
		_ifstr.open(fileName);
		std::string str;
		_ifstr >> str;
		_stroke_len = atoi(str.c_str());
		s.push_back(str);
		str.clear();
		s.push_back("\n");
		int i = 0;
		while (!_ifstr.eof())
		{
			i++;
			str.clear();
			_ifstr >> str;
			s.push_back(str);
			if (i == _stroke_len)
			{
				s.push_back("\n");
				i = 0;
			}
			else
			{
				s.push_back(" ");
			}
		}
		_ifstr.close();
		s.push_back(value);
		_ofstr.open(fileName);
		for (i = 0; i < s.size();i++)_ofstr << s[i];
		_ofstr.close();
		s.clear();
	}

	void texter::addToFile(std::string fileName, float value) {}

	std::string texter::downloadFromFile(std::string fileName)
	{ 
		std::vector<std::string> s;
		_ifstr.open(fileName);
		std::string str;
		_ifstr >> str;
		_stroke_len = atoi(str.c_str());
		s.push_back(str);
		str.clear();
		s.push_back("\n");
		int i = 0;
		while (!_ifstr.eof())
		{
			i++;
			str.clear();
			_ifstr >> str;
			s.push_back(str);
			if (i == _stroke_len)
			{
				s.push_back("\n");
				i = 0;
			}
			else
			{
				s.push_back(" ");
			}
		}
		_ifstr.close();
		str.clear();
		str = s[0];
		for (i = 1; i < s.size(); i++) str+=s[i];
		s.clear();
		return str; 
	}

	std::vector<std::string> texter::downloadFromFile_Vector(std::string fileName)
	{
		std::vector<std::string> str_M;
		_ifstr.open(fileName);
		std::string str;
		while (!_ifstr.eof())
		{
			str.clear();
			_ifstr >> str;
			str_M.push_back(str);
		}
		return str_M;
	}