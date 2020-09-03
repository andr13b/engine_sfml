#pragma once
#include <vector>
#include "unit.h"
#include "discreteMap.h"

/*
отряд юнитов
*/
class unitSquad
{
private:
	std::vector<unit> units;
	//приказы отряду
	std::list<order> orders;
public:
	unitSquad();
	~unitSquad();

	
	
	void spawnUnitLine(int amoount, PAO2d leaderpao, float stepBetweenUnits, Drawler &dr);

	void setGoalPath(std::list<order> nOrders);
	void addOrder(std::list<order> nOrders);
	void addOrder(order nOrder);
	void readOrders(discreteMap &dMap);
	void update(discreteMap &dMap);
	void draw(Drawler &dr);
};




