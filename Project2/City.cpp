#include "City.h"

City::City()
	: name(""), distance(0), neighboursCount(0), posX(0), posY(0), visited(false), neighbours(0)
{
}

City::City(String name, int posX, int posY, int distance)
	: name(name), distance(distance), neighboursCount(0), posX(posX), posY(posY), visited(false), neighbours(VECTOR_START_SIZE)
{
	if (this->getName() != "") {
		//std::cout << this->getName() << " constructor (" << this << ")\n";
	}
}

City::City(const City& other)
	: name(other.name), distance(other.distance), neighboursCount(other.neighboursCount), posX(other.posX), posY(other.posY), neighbours(other.neighbours), visited(other.visited)
{
}

City::~City()
{
	if (this->getName() != "") {
		//std::cout << this->getName() << " destructor (" << this << ")\n";
	}
}

City& City::operator=(const City& other)
{
	if (this == &other) {
		return *this;
	}
	name = other.name;
	distance = other.distance;
	neighboursCount = other.neighboursCount;
	posX = other.posX;
	posY = other.posY;
	neighbours = other.neighbours;
	visited = other.visited;
	return *this;
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

void City::increaseNeighboursCount()
{
	neighboursCount++;
}

void City::setNeighboursCount(int neighboursCount)
{
	this->neighboursCount = neighboursCount;
}

int City::getNeighboursCount()
{
	return this->neighboursCount;
}

void City::addNeighbour(City neighbour)
{
	
}
