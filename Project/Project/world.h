#pragma once

#include <vector>
#include "unit.h"

/*
объекты, наполн€ющие мир
*/
class world
{
private:
	std::vector<unit> unitSquad;
	Drawler &dr;
public:
	
	world(Drawler &d);
	~world();


	void spawnUnitLine(int amoount, PAO2d leaderpao, float stepBetweenUnits);


	void update(PAO2d goal);

	void draw();
};

