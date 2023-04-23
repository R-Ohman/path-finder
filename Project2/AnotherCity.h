#pragma once
#include "Parameters.h"

class City;

class AnotherCity {
public:
	int distance;
	City* city;
	AnotherCity* prev_city;
	bool visited;

	AnotherCity() : distance(0), city(nullptr), prev_city(nullptr), visited(false) {}

	AnotherCity(int distance, City* city)
		: distance(distance), city(city), prev_city(nullptr), visited(false) {}
};