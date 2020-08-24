#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

	class texter
	{
	private:
		std::ifstream _ifstr;
		std::ofstream _ofstr;
		int _stroke_len = 1;
	protected:
	
	public:		
		texter();
		~texter();
		void uploadToFile(std::string fileName, std::string value);
		void uploadToFile(std::string fileName, char * value);
		void uploadToFile(std::string fileName, float value);
		void addToFile(std::string fileName, std::string value);
		void addToFile(std::string fileName, float value);
		std::string downloadFromFile(std::string fileName);
		
		std::vector<std::string> downloadFromFile_Vector(std::string fileName);
		
	};

