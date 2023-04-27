#pragma once
#include "Parameters.h"

class City
{
private:
    char name[CITY_NAME_BUFFER];
	int posX, posY;

public:
    City();
    City(char* name, int posX, int posY);
    City(const City& other);
    ~City();

    City& operator=(const City& other);

    int getPosX() const;
    int getPosY() const;
    
    char* getName();

	Vector<AnotherCity> neighbours;     // Array of neighbours and flights (with distances)
    bool visited;
};