#include <iostream>
#include "Parameters.h"

int AnotherCity::idCounter = 0;

void dijkstra (CitiesGraph& graph, const String& startCity, const String& endCity, int typeOfSearch) {
	
	HashMap<AnotherCity* > graphCities;

	for (int i = 0; i < graph.citiesNames.GetSize(); i++) {
		if (graph.citiesNames[i] == startCity) {
			graphCities.putValue(graph.citiesNames[i], new AnotherCity(0, graph.cities[graph.citiesNames[i]]));
		}
		else {
			graphCities.putValue(graph.citiesNames[i], new AnotherCity(INT_MAX, graph.cities[graph.citiesNames[i]]));
		}
	}
	MinHeap queue;
	queue.insert(graphCities[startCity]);
	HashMap<bool> addedToQueue;
	
	while (!queue.empty()) {
		AnotherCity* current = queue.extractMin();
		if (current->visited) {
			continue;
		}
		current->visited = true;
		
		for (int i = 0; i < current->city->neighbours.GetSize(); i++) {
			if (graphCities[current->city->neighbours[i].city->getName()]->distance > current->distance + current->city->neighbours[i].distance
				) {
				graphCities[current->city->neighbours[i].city->getName()]->distance = current->distance + current->city->neighbours[i].distance;
				/*if (addedToQueue.containsKey(current->city->neighbours[i].city->getName())) {
					addedToQueue.putValue(current->city->neighbours[i].city->getName(), true);
					queue.insert(graphCities[current->city->neighbours[i].city->getName()]);
				}*/
				queue.insert(graphCities[current->city->neighbours[i].city->getName()]);
				graphCities[current->city->neighbours[i].city->getName()]->prev_city = current;
			}
		}
	}
	// print the path and distance

	AnotherCity* current = graphCities[endCity];
	Vector<String> path(VECTOR_START_SIZE);
	while (current->prev_city != nullptr) {
		path.push_back(current->city->getName());
		current = current->prev_city;
	}
	path.push_back(current->city->getName());
	std::cout << graphCities[endCity]->distance;
	
	if (typeOfSearch == 1) {
		for (int i = path.GetSize() - 2; i > 0; i--) {
			std::cout << " " << path[i];
		}
	}
	std::cout << std::endl;
}


int stringToInt(const String& strNum) {
	int num = 0;
	for (int i = 0; i < strNum.GetLength(); i++) {
		num = num * 10 + (strNum[i] - '0');
	}
	return num;
}


void readFlights(CitiesGraph& graph)
{
	int countOfFlights;
	std::cin >> countOfFlights;

	char from[100], to[100];
	int time;
	for (int i = 0; i < countOfFlights; i++) {
		std::cin >> from >> to >> time;
		graph.addNeighbour(from, to, time);
	}
}


void readCommands(CitiesGraph& graph)
{
	char from[100], to[100];
	int countOfCommands, typeOfSearch;
	std::cin >> countOfCommands;

	for (int i = 0; i < countOfCommands; i++) {
		std::cin >> from >> to >> typeOfSearch;

		String startCity(from), endCity(to);
		dijkstra(graph, startCity, endCity, typeOfSearch);
	}
}


int main()
{
	int width, height;
	std::cin >> width >> height;

	char** map = new char* [height];
	
	for (int i = 0; i < height; i++) {
		map[i] = new char[width];
	}
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cin >> map[i][j];
		}
	}

	CitiesGraph graph(map, height, width);

	readFlights(graph);

	readCommands(graph);

	//graph.printCities();
	
}
