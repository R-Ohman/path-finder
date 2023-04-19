#pragma once
#include "Parameters.h"

class City;

class CitiesGraph
{
private:
	Vector<String> citiesNames;
	HashMap<City *> cities;
	
	
public:
	CitiesGraph(char** map, int h, int w);
	
	void printCities();
	
	~CitiesGraph();
};

