#include <iostream>
#include "Parameters.h"


int AnotherCity::idCounter = 0;

void dijkstra (CitiesGraph& graph, char* startCity, char* endCity, int typeOfSearch) {
	
	if (strcmp(startCity, endCity) == 0) {
		std::cout << 0 << "\n";
		return;
	}
	
	HashMap<AnotherCity* > graphCities;


	graphCities.putValue(startCity, new AnotherCity(0, graph.cities[startCity]));
	graphCities.putValue(endCity, new AnotherCity(INT_MAX, graph.cities[endCity]));
	
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

			if (!graphCities.containsKey(current->city->neighbours[i].city->getName())
				) {
				// WARN
				AnotherCity* newCity = new AnotherCity(current->distance + current->city->neighbours[i].distance, // check me .distance
														current->city->neighbours[i].city);
				graphCities.putValue(newCity->city->getName(), newCity);
				queue.insert(newCity);
			//	std::cout << "Added to queue " << current->city->neighbours[i].city->getName() << " [" << graphCities[newCity->city->getName()]->distance << "]\n";
				graphCities[newCity->city->getName()]->prev_city = current;
			}
			else if (graphCities[current->city->neighbours[i].city->getName()]->distance > current->distance + current->city->neighbours[i].distance
				) {
				graphCities[current->city->neighbours[i].city->getName()]->distance = current->distance + current->city->neighbours[i].distance;
				/*if (addedToQueue.containsKey(current->city->neighbours[i].city->getName())) {
					addedToQueue.putValue(current->city->neighbours[i].city->getName(), true);
					queue.insert(graphCities[current->city->neighbours[i].city->getName()]);
				}*/
				queue.insert(graphCities[current->city->neighbours[i].city->getName()]);
			//	std::cout << "Added to queue " << current->city->neighbours[i].city->getName() << " [" << graphCities[current->city->neighbours[i].city->getName()]->distance << "]\n";
				graphCities[current->city->neighbours[i].city->getName()]->prev_city = current;
			}
		}
	}
	// print the path and distance

	AnotherCity* current = graphCities[endCity];
	Vector< char*> path(VECTOR_START_SIZE);
	
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


//int stringToInt(const String& strNum) {
//	int num = 0;
//	for (int i = 0; i < strNum.GetLength(); i++) {
//		num = num * 10 + (strNum[i] - '0');
//	}
//	return num;
//}


void readFlights(CitiesGraph& graph)
{
	int countOfFlights;
	std::cin >> countOfFlights;

	char from[CITY_NAME_BUFFER], to[CITY_NAME_BUFFER];
	int time;
	for (int i = 0; i < countOfFlights; i++) {
		std::cin >> from >> to >> time;
		graph.addNeighbour(from, to, time);
	}
}


void readCommands(CitiesGraph& graph)
{
	char from[CITY_NAME_BUFFER], to[CITY_NAME_BUFFER];
	int countOfCommands, typeOfSearch;
	std::cin >> countOfCommands;

	for (int i = 0; i < countOfCommands; i++) {
		std::cin >> from >> to >> typeOfSearch;

		dijkstra(graph, from, to, typeOfSearch);
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
			//std::cin >> map[i][j];
			map[i][j] = getchar();
			if (map[i][j] == '\n') {
				map[i][j] = getchar();
			}
		}
	}

	CitiesGraph graph(map, height, width);

	readFlights(graph);

	graph.printCities();
	
	readCommands(graph);

	
}
