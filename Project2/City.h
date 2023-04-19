#pragma once

#include "Parameters.h"

class City
{
private:
	String name;
	int distance;
	int neighboursCount;
	int posX, posY;

public:
	City();
	City(String name, int posX, int posY);
	~City();

	int getPosX();
	int getPosY();
	
	void setName(String name);
	String getName();
	
	void setDistance(int distance);
	int getDistance();

	void setNeighboursCount(int neighboursCount);
	int getNeighboursCount();
	
	City** neighborus;
	bool visited;
};

