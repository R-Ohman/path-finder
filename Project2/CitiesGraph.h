#pragma once
#include "Parameters.h"

class City;

class CitiesGraph
{
private:
	struct spot {
		int x, y, distance;
		spot(int x = -1, int y = -1, int distance = 0) : x(x), y(y), distance(distance) {}
	};
	
	char** map;
	bool** visited;
	int height, width;
	
	Vector<String> citiesNames;
	HashMap<City *> cities;
	
	void getCities();
	void lookForNeighbours(const String& cityName);
	void continueLookinfForNeighbour(Vector<spot>& queue, spot current);
	
public:
	CitiesGraph(char** map, int h, int w);
	
	void addNeighbour(const String& from, const String& to, int distance);
	
	void printCities();
	
	~CitiesGraph();
};

