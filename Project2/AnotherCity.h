#pragma once
#include "Parameters.h"

class City;

class AnotherCity {
public:
    static int idCounter;       // number of created objects
	int distance;               // distance from start city to this city
    int id;                     // for comparing in min heap 
	City* city;                 // pointer to current city
	AnotherCity* prev_city;     // pointer to city, from which we came to this city
    bool visited;

    AnotherCity() : distance(0), id(0), city(nullptr), prev_city(nullptr), visited(false) {}

    AnotherCity(int distance, City* city)
        : distance(distance), city(city), prev_city(nullptr), visited(false)
    {
        id = ++idCounter;
    }
};