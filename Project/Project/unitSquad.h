#pragma once
#include <vector>
#include "unit.h"

class unitSquad
{
private:
	std::vector<unit> units;
public:
	unitSquad();
	~unitSquad();



	void spawnUnitLine(int amoount, PAO2d leaderpao, float stepBetweenUnits, Drawler &dr);
	void update(PAO2d goal);
	void draw(Drawler &dr);
};

