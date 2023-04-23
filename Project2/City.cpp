#include "City.h"

City::City()
	: name(""), posX(0), posY(0), visited(false), neighbours(0)
{
	//std::cout << "City default constructor [" << ++constructorCounter << "]\n";
}

City::City(String name, int posX, int posY, int distance)
	: name(name), posX(posX), posY(posY), visited(false), neighbours(VECTOR_START_SIZE)
{
	//std::cout << "City constructor [" << ++constructorCounter << "]\n";
	if (this->getName() != "") {
		//std::cout << this->getName() << " constructor (" << this << ")\n";
	}
}

City::City(const City& other)
	: name(other.name), posX(other.posX), posY(other.posY), neighbours(other.neighbours), visited(other.visited)
{
	//std::cout << "City copy constructor [" << ++constructorCounter << "]\n";
}

City::~City()
{
	//std::cout << "City destructor [" << ++destructorCounter << "]\n";
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

void City::setName(const String& name)
{
	this->name = name;
}

String City::getName()
{
	return this->name;
}