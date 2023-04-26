#include "City.h"

City::City()
    : posX(0), posY(0), visited(false), neighbours(0)
{
    name[0] = '\0';
    //std::cout << "City default constructor [" << ++constructorCounter << "]\n";
}

City::City(char* name, int posX, int posY, int distance)
    : posX(posX), posY(posY), visited(false), neighbours(VECTOR_START_SIZE)
{
    for (int i = 0; i < CITY_NAME_BUFFER; i++) {
        this->name[i] = name[i];
        if (name[i] == '\0') {
            break;
        }
    }
    /*std::cout << "City constructor [" << ++constructorCounter << "]\n";
    if (this->getName() != "") {
            std::cout << this->getName() << " constructor (" << this << ")\n";
    }*/
}

City::City(const City& other)
    : posX(other.posX), posY(other.posY), neighbours(other.neighbours), visited(other.visited)
{
    for (int i = 0; i < CITY_NAME_BUFFER; i++) {
        this->name[i] = other.name[i];
        if (other.name[i] == '\0') {
            break;
        }
    }
    //std::cout << "City copy constructor [" << ++constructorCounter << "]\n";
}

City::~City()
{
    /*std::cout << "City destructor [" << ++destructorCounter << "]\n";
    if (this->getName() != "") {
            std::cout << this->getName() << " destructor (" << this << ")\n";
    }*/
}

City& City::operator=(const City& other)
{
    if (this == &other) {
        return *this;
    }
    for (int i = 0; i < CITY_NAME_BUFFER; i++) {
        this->name[i] = other.name[i];
        if (other.name[i] == '\0') {
            break;
        }
    }
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
    for (int i = 0; i < CITY_NAME_BUFFER; i++) {
        this->name[i] = name[i];
        if (name[i] == '\0') {
            break;
        }
    }
}

char* City::getName()
{
    return this->name;
}