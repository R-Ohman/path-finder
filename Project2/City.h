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
	City(const City& other);
	~City();

	City& operator=(const City& other);

	int getPosX();
	int getPosY();
	
	void setName(String name);
	String getName();
	
	void setDistance(int distance);
	int getDistance();
	void increaseNeighboursCount();

	void setNeighboursCount(int neighboursCount);
	int getNeighboursCount();
	void addNeighbour(City neighbour);
	
	Vector<City> neighbours;
	bool visited;
};

