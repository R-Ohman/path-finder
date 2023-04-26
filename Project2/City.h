#pragma once

#include "Parameters.h"


class City
{
private:
    char name[CITY_NAME_BUFFER];
    int posX, posY;

public:
    City();
    City(char* name, int posX, int posY, int distance = 0);
    City(const City& other);
    ~City();

    City& operator=(const City& other);

    int getPosX();
    int getPosY();

    void setName(char* name);
    char* getName();

    //void addNeighbour(City neighbour);

    Vector<AnotherCity> neighbours;
    bool visited;
};