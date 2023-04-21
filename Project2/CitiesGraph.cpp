#include "CitiesGraph.h"

CitiesGraph::CitiesGraph(char** map, int h, int w) : citiesNames(VECTOR_START_SIZE)
{
	//citiesNames.init();
	
	// Iterate all the map and find the cities (*) and its names
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			// City is found
			if (map[i][j] == '*') {
				String cityName;
				// Check all the neighbours, there must be a city name
				for (int k = -1; k < 2; k++) {
					for (int m = -1; m < 2; m++) {
						if (cityName.GetLength() > 0) {
							break;
						}
						if (j + m < 0 || j + m >= w || i + k < 0 || i + k >= h) {
							continue;
						}
						// One of the letters is found
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

							cities.putValue(cityName, new City(cityName, j, i));
							//std::cout << "(" << j << ", " << i << ") " << cityName << "\n";
							citiesNames.push_back(cityName);
							break;
						}
					}
				}
			}
		}
	}

	struct spot {
		int x, y;
		int distance;

		spot(int x = -1, int y = -1, int distance = 0) : x(x), y(y), distance(distance) {}
	};

	for (int i = 0; i < citiesNames.GetSize(); i++) {
		int counter = 0;
		bool** visited = new bool* [h];
		for (int k = 0; k < h; k++) {
			visited[k] = new bool[w];
			for (int m = 0; m < w; m++) {
				visited[k][m] = false;
			}
		}

		Vector<spot> queue(VECTOR_START_SIZE);
		//queue.init();
		int startCityPosX = cities[citiesNames[i]]->getPosX();
		int startCityPosY = cities[citiesNames[i]]->getPosY();

		queue.push_back(spot(startCityPosX, startCityPosY));

		while (queue.GetSize()) {
			bool endOfSearch = false;
			spot current = queue.pop_back();

			if (visited[current.y][current.x]) {
				continue;
			}

			if (map[current.y][current.x] == '*') {
				
				if (current.x != startCityPosX || current.y != startCityPosY) {
					// found neighbour
					for (int j = 0; j < citiesNames.GetSize(); j++) {
						if (cities[citiesNames[j]]->getPosX() == current.x
							&& cities[citiesNames[j]]->getPosY() == current.y
							) {

							// Check if the neighbour is already in the list and it has less distance
							for (int k = 0; k < cities[citiesNames[i]]->getNeighboursCount(); k++) {
								

								if (cities[citiesNames[i]]->neighbours[k].getName() == citiesNames[j]
									&& cities[citiesNames[i]]->neighbours[k].getDistance() > current.distance
									) {
									
									std::cout << "FLAG | " << cities[citiesNames[i]]->getName() << " | " << cities[citiesNames[j]]->getName() << " [" << current.distance << "] " << cities[citiesNames[i]]->neighbours[k].getName() << "[" << cities[citiesNames[i]]->neighbours[k].getDistance() << "]" << "\n";

									cities[citiesNames[i]]->neighbours[k].setDistance(current.distance);
									endOfSearch = true;
									break;
								}
							}
							if (endOfSearch) {
								break;
							}
							// Add count of neighbours
							cities[citiesNames[i]]->increaseNeighboursCount();
							//cities[citiesNames[j]]->increaseNeighboursCount();
							// Add new neighbour
							cities[citiesNames[i]]->neighbours.push_back(*cities[citiesNames[j]]);
							// Add distance to added neighbour
							//cities[citiesNames[i]]->neighbours[cities[citiesNames[i]]->
							//	neighbours.GetSize() - 1].neighbours.init();

							cities[citiesNames[i]]->neighbours[cities[citiesNames[i]]->
								neighbours.GetSize() - 1].setDistance(current.distance);
							endOfSearch = true;
							break;
						}

					}
				}
			}
			if (endOfSearch) {
				continue;
			}
			
			visited[current.y][current.x] = true;
			
			for (int n = -1; n < 2; n += 2) {
				if (current.x + n >= 0 && current.x + n < w
					&& (map[current.y][current.x + n] == '#' || map[current.y][current.x + n] == '*')
					&& !visited[current.y][current.x + n]
					) {
					queue.push_back(spot(current.x + n, current.y, current.distance + 1));
				}
				
				if (current.y + n >= 0 && current.y + n < h
					&& (map[current.y + n][current.x] == '#' || map[current.y + n][current.x] == '*')
					&& !visited[current.y + n][current.x]
					) {
					queue.push_back(spot(current.x, current.y + n, current.distance + 1));
				}
			}
			
		}
	}

}


void CitiesGraph::printCities()
{
	for (int i = 0; i < citiesNames.GetSize(); i++) {
		std::cout << "City: " << cities[citiesNames[i]]->getName() << "(" << cities[citiesNames[i]]->getPosX() << ", " << cities[citiesNames[i]]->getPosY() << ")" << "\n\t";
		std::cout << "Neighbours:\n\t\t";
		for (int j = 0; j < cities[citiesNames[i]]->getNeighboursCount(); j++) {
			std::cout << cities[citiesNames[i]]->neighbours[j].getName() << "(" << cities[citiesNames[i]]->neighbours[j].getDistance() << ")\n";
			if (j < cities[citiesNames[i]]->getNeighboursCount() - 1) {
				std::cout << "\t\t";
			}
		}
	}
}

CitiesGraph::~CitiesGraph()
{
}
