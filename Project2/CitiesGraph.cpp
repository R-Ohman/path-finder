#include "CitiesGraph.h"




CitiesGraph::CitiesGraph(char** map, int h, int w) : citiesNames(VECTOR_START_SIZE), height(h), width(w), map(map)
{
	visited = new bool* [height];
	for (int k = 0; k < height; k++) {
		visited[k] = new bool[width];
	}
	
	getCities();

	for (int i = 0; i < citiesNames.GetSize(); i++)
	{
		for (int k = 0; k < height; k++) {
			for (int m = 0; m < width; m++) {
				visited[k][m] = false;
			}
		}
		lookForNeighbours(citiesNames[i]);
	}

}

void CitiesGraph::addNeighbour(const String& from, const String& to, int distance)
{
	for (int i = 0; i < cities[from]->neighbours.GetSize(); i++)
	{
		if (cities[from]->neighbours[i].city->getName() == to)
		{
			if (cities[from]->neighbours[i].distance > distance)
			{
				cities[from]->neighbours[i].distance = distance;
			}
			return;
		}
	}
	
	AnotherCity newNeighbour(distance, cities[to]);
	cities[from]->neighbours.push_back(newNeighbour);
}


void CitiesGraph::getCities()
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			// City is found
			if (map[i][j] == '*') {
				String cityName;
				// Check all the neighbours, there must be a city name
				for (int k = -1; k < 2; k++) {
					for (int m = -1; m < 2; m++) {
						if (cityName.GetLength() > 0) {
							break;
						}
						if (j + m < 0 || j + m >= width || i + k < 0 || i + k >= height) {
							continue;
						}
						// One of the letters is found
						if (map[i + k][j + m] != '.' && map[i + k][j + m] != '#' && map[i + k][j + m] != '*') {
							int tmpX1 = j + m, tmpX2 = j + m + 1;
							// read the name to the left border
							while (tmpX1 >= 0 && map[i + k][tmpX1] != '.' && map[i + k][tmpX1] != '#' && map[i + k][tmpX1] != '*') {

								cityName.PushFront(map[i + k][tmpX1]);
								tmpX1--;
							}
							// read the name to the right border
							while (tmpX2 < width && map[i + k][tmpX2] != '.' && map[i + k][tmpX2] != '#' && map[i + k][tmpX2] != '*') {
								cityName += map[i + k][tmpX2];
								tmpX2++;
							}
							// WARN i -> j, j -> i
							cities.putValue(cityName, new City(cityName, j, i));
							
							citiesNames.push_back(cityName);
							break;
						}
					}
				}
			}
		}
	}
}

void CitiesGraph::lookForNeighbours(const String& cityName)
{
	
	PrioritySpot queue;

	int startCityPosX = cities[cityName]->getPosX();
	int startCityPosY = cities[cityName]->getPosY();

	queue.insert(spot(startCityPosX, startCityPosY));

	while (!queue.empty()) {
		bool endOfSearch = false;
		spot current = queue.extractMin();

		if (visited[current.y][current.x]) {
			continue;
		}

		if (map[current.y][current.x] == '*' && !(current.x == startCityPosX && current.y == startCityPosY)) {

				// found neighbour
				for (int j = 0; j < citiesNames.GetSize(); j++) {
					if (cities[citiesNames[j]]->getPosX() == current.x
						&& cities[citiesNames[j]]->getPosY() == current.y
						) {

						// Check if the neighbour is already in the list and it has less distance
						for (int k = 0; k < cities[cityName]->neighbours.GetSize(); k++) {
							
							if (cities[cityName]->neighbours[k].city->getName() == citiesNames[j])
							{
								
								if (cities[cityName]->neighbours[k].distance > current.distance) {
									cities[cityName]->neighbours[k].distance = current.distance;
								}
								endOfSearch = true;
								break;
							}
						}
						if (endOfSearch) {
							break;
						}
						// Add new neighbour
						AnotherCity newNeighbour(current.distance, cities[citiesNames[j]]);
						cities[cityName]->neighbours.push_back(newNeighbour);
						//endOfSearch = true; | WARN
						break;
					}

				}
		}
		else if (map[current.y][current.x] == '#' || current.x == startCityPosX && current.y == startCityPosY) {

			visited[current.y][current.x] = true;

			continueLookinfForNeighbour(queue, current);
		}
	}
}


void CitiesGraph::continueLookinfForNeighbour(PrioritySpot& queue, spot& current)
{
	for (int n = -1; n < 2; n += 2) {
		if (current.x + n >= 0 && current.x + n < width
			&& (map[current.y][current.x + n] == '#' || map[current.y][current.x + n] == '*')
			&& !visited[current.y][current.x + n]
			) {

			queue.insert(spot(current.x + n, current.y, current.distance + 1));
		}

		if (current.y + n >= 0 && current.y + n < height
			&& (map[current.y + n][current.x] == '#' || map[current.y + n][current.x] == '*')
			&& !visited[current.y + n][current.x]
			) {

			queue.insert(spot(current.x, current.y + n, current.distance + 1));
		}
	}
}


void CitiesGraph::printCities()
{
	for (int i = 0; i < citiesNames.GetSize(); i++) {
		std::cout << "City: " << cities[citiesNames[i]]->getName() << "(" << cities[citiesNames[i]]->getPosX() << ", " << cities[citiesNames[i]]->getPosY() << ")" << "\n\t";
		for (int j = 0; j < cities[citiesNames[i]]->neighbours.GetSize(); j++) {
			if (j == 0) {
				std::cout << "Neighbours:\n\t\t";
			}
			std::cout << cities[citiesNames[i]]->neighbours[j].city->getName() << "(" << cities[citiesNames[i]]->neighbours[j].distance << ")\n";
			if (j < cities[citiesNames[i]]->neighbours.GetSize() - 1) {
				std::cout << "\t\t";
			}
		}
	}
}

CitiesGraph::~CitiesGraph()
{
	for (int i = 0; i < citiesNames.GetSize(); i++) {
		delete cities[citiesNames[i]];
	}
	for (int i = 0; i < height; i++) {
		delete[] map[i];
		delete[] visited[i];
	}
	delete[] map;
	delete[] visited;
}
