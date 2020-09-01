#pragma once
/*
���������� �����,
*/
struct discreteMap
{
	int **_M;//������ �����//0 - ��� ��������, 1 - ������, 2 - �����������
	sf::Vector2i _mapSize;//����������� ����� � �������
	sf::Vector2f _cellSize;//������ ������ ���������� �����
	bool initialyzed = false;
	//�������� ����� ������ �� ��������� �� ������
	sf::Vector2i cellNum(sf::Vector2f pixelPos)
	{
		sf::Vector2i CN;
		CN.x = pixelPos.x / _cellSize.x;
		CN.y = pixelPos.y / _cellSize.y;
		return CN;
	}
	//���������� ����� ������ �� � ������
	sf::Vector2f cellCentre(sf::Vector2i cellNum)
	{
		sf::Vector2f CC;
		CC.x = (0.5f + (float)cellNum.x)*_cellSize.x;
		CC.y = (0.5f + (float)cellNum.y)*_cellSize.y;
		return CC;
	}
	//������ � �������� �������
	bool inBorders(sf::Vector2i index)
	{
		if (index.x >= 0 && index.y >= 0 && index.x < _mapSize.x || index.y < _mapSize.y)return true;
		return false;
	}


};




