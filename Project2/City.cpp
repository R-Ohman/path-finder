#include "City.h"

City::City()
    : posX(0), posY(0), visited(false), neighbours(0)
{
    name[0] = '\0';
}

City::City(char* name, int posX, int posY, int distance)
    : posX(posX), posY(posY), visited(false), neighbours(VECTOR_START_SIZE)
{
	strcpy(this->name, name);
}

City::City(const City& other)
    : posX(other.posX), posY(other.posY), neighbours(other.neighbours), visited(other.visited)
{
	strcpy(this->name, other.name);
}

City::~City()
{
}

City& City::operator=(const City& other)
{
    if (this == &other) {
        return *this;
    }
	strcpy(this->name, other.name);
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

void City::setName(char* name)
{
	strcpy(this->name, name);
}

char* City::getName()
{
    return this->name;
}