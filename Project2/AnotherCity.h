#pragma once
#include "Parameters.h"

class City;

class AnotherCity {
public:
    static int idCounter;
    int distance;
    int id;
    City* city;
    AnotherCity* prev_city;
    bool visited;

    AnotherCity() : distance(0), city(nullptr), prev_city(nullptr), visited(false), id(0) {}

    AnotherCity(int distance, City* city)
        : distance(distance), city(city), prev_city(nullptr), visited(false)
    {
        id = ++idCounter;
    }
};