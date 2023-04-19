#include "CitiesGraph.h"

CitiesGraph::CitiesGraph(char** map, int h, int w)
{
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (map[i][j] == '*') {
				String cityName;
				for (int k = -1; k < 2; k++) {
					for (int m = -1; m < 2; m++) {
						if (cityName.GetLength() > 0) {
							break;
						}
						if (j + m < 0 || j + m >= w || i + k < 0 || i + k >= h) {
							continue;
						}
						if (map[i + k][j + m] >= 'A' && map[i + k][j + m] <= 'Z') {
							int tmpX1 = j + m, tmpX2 = j + m + 1;
							// read the name to the left border
							while (tmpX1 >= 0 && map[i + k][tmpX1] >= 'A' && map[i + k][tmpX1] <= 'Z') {
								
								cityName.PushFront(map[i + k][tmpX1]);
								tmpX1--;
							}
							// read the name to the right border
							while (tmpX2 < w && map[i + k][tmpX2] >= 'A' && map[i + k][tmpX2] <= 'Z') {
								cityName += map[i + k][tmpX2];
								tmpX2++;
							}
							cities.push_back(new City(cityName, j, i));
							break;
						}
					}
				}
			}
		}
	}
}

void CitiesGraph::printCities()
{
	for (int i = 0; i < cities.GetSize(); i++) {
		std::cout << cities[i]->getName() << " " << cities[i]->getPosX() << " " << cities[i]->getPosY() << std::endl;
	}
}

CitiesGraph::~CitiesGraph()
{
}
