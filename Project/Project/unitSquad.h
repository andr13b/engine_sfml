#pragma once
#include <vector>
#include "unit.h"
#include "discreteMap.h"


class unitSquad
{
private:
	std::vector<unit> units;
public:
	unitSquad();
	~unitSquad();

	
	
	void spawnUnitLine(int amoount, PAO2d leaderpao, float stepBetweenUnits, Drawler &dr);

	void setupGoals(discreteMap &dMap);
	void update(discreteMap &dMap);
	void draw(Drawler &dr);
};




