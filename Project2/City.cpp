#include "City.h"

City::City()
    : posX(0), posY(0), neighbours(0), visited(false)
{
    name[0] = '\0';
}

City::City(char* name, int posX, int posY)
    : posX(posX), posY(posY), neighbours(VECTOR_START_SIZE), visited(false)
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

int City::getPosX() const
{
    return this->posX;
}

int City::getPosY() const
{
    return this->posY;
}

char* City::getName()
{
    return this->name;
}