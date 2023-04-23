#pragma once

#include "Parameters.h"


class City
{
private:
	String name;
	int posX, posY;

public:
	City();
	City(String name, int posX, int posY, int distance = 0);
	City(const City& other);
	~City();

	City& operator=(const City& other);

	int getPosX();
	int getPosY();
	
	void setName(const String& name);
	String getName();
	
	//void addNeighbour(City neighbour);
	
	Vector<AnotherCity> neighbours;
	bool visited;
};

