#include "City.h"

City::City() : name(""), distance(0), neighboursCount(0), neighborus(nullptr), posX(0), posY(0), visited(false)
{
}

City::City(String name, int posX, int posY) : name(name), distance(0), neighboursCount(0), neighborus(nullptr), posX(posX), posY(posY), visited(false)
{
}

City::~City()
{
	if (neighborus != nullptr) {
		for (int i = 0; i < neighboursCount; i++) {
			delete neighborus[i];
		}
		delete[] neighborus;
	}
}

int City::getPosX()
{
	return this->posX;
}

int City::getPosY()
{
	return this->posY;
}

void City::setName(String name)
{
	this->name = name;
}

String City::getName()
{
	return this->name;
}

void City::setDistance(int distance)
{
	this->distance = distance;
}

int City::getDistance()
{
	return this->distance;
}

void City::setNeighboursCount(int neighboursCount)
{
	this->neighboursCount = neighboursCount;
}

int City::getNeighboursCount()
{
	return this->neighboursCount;
}
