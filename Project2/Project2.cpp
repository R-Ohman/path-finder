#include <iostream>
#include "Parameters.h"

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
	
	graph.printCities();
	
}
