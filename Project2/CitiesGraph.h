#pragma once
#include "Parameters.h"

class City;

class CitiesGraph
{
private:

    struct spot
    {
        int x, y, distance;
        spot(int x = -1, int y = -1, int distance = 0)
            : x(x), y(y), distance(distance) {}
    };

	class PrioritySpot;     // Priority queue of spots (used for searching neighbours)

    char** map;
    bool** visited;
    int height, width;
    HashMap<City*> cities;

	char* getCityName(int x, int y);    // Returns the name of the city at the given coordinates

	void getCities();                   // Iterate through the map and find all cities and their neighbours
    void lookForNeighbours(char* cityName);
	void continueLookinfForNeighbour(PrioritySpot& queue, spot& current) const;   // Add the neighbour spots of the current spot to the queue

public:
	CitiesGraph(char** map, int h, int w);   // Make a graph from the given map


	void addNeighbour(char* from, char* to, int distance);  // Add a flight between two cities

    void printCities();

    void dijkstra(char* startCity, char* endCity, int typeOfSearch);

    CitiesGraph(const CitiesGraph& other);
    CitiesGraph& operator=(const CitiesGraph& other);
    ~CitiesGraph();
};