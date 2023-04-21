#include <iostream>
#include "Parameters.h"

int stringToInt(const String& strNum) {
	int num = 0;
	for (int i = 0; i < strNum.GetLength(); i++) {
		num = num * 10 + (strNum[i] - '0');
	}
	return num;
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

	int countOfFlights;
	std::cin >> countOfFlights;

	char from[100], to[100];
	int time;
	for (int i = 0; i < countOfFlights; i++) {
		std::cin >> from >> to >> time;
		graph.addNeighbour(from, to, time);
	}

	int countOfCommands, typeOfSearch;
	std::cin >> countOfCommands;
	
	for (int i = 0; i < countOfCommands; i++) {
		std::cin >> from >> to >> typeOfSearch;
	}

	graph.printCities();
	
}
