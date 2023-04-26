﻿#include "CitiesGraph.h"


CitiesGraph::CitiesGraph(char** map, int h, int w) : height(h), width(w), map(map)
{
    visited = new bool* [height];
    for (int k = 0; k < height; k++) {
        visited[k] = new bool[width];
        for (int m = 0; m < width; m++) {
            visited[k][m] = false;
        }
    }

    getCities();
    //if (width == 2048) std::cout << "Cities count: " << citiesNames.GetSize() << "\n\n";

}


char* CitiesGraph::getCityName(int x, int y)
{
    for (int k = -1; k < 2; k++) {
        for (int m = -1; m < 2; m++) {
            if (x + m < 0 || x + m >= width || y + k < 0 || y + k >= height) {
                continue;
            }
            // One of the letters is found
            if (map[y + k][x + m] != '.' && map[y + k][x + m] != '#' && map[y + k][x + m] != '*') {
                int tmpX = x + m, i = 0;
                // read the name to the left border
                while (tmpX >= 0 && map[y + k][tmpX] != '.' && map[y + k][tmpX] != '#' && map[y + k][tmpX] != '*') {
                    tmpX--;
                }
                static char buffer[CITY_NAME_BUFFER];
                //std::cout << "Before: " << buffer << " | After: " << '\n';
                // read the name to the right border
                while (++tmpX < width && map[y + k][tmpX] != '.' && map[y + k][tmpX] != '#' && map[y + k][tmpX] != '*') {
                    buffer[i++] = map[y + k][tmpX];
                }
                buffer[i] = '\0';
                //std::cout << buffer << '\n';
                return buffer;
            }
        }
    }
    return nullptr;
}


void CitiesGraph::addNeighbour(char* from, char* to, int distance)
{
    for (int i = 0; i < cities[from]->neighbours.GetSize(); i++)
    {
        if (strcmp(cities[from]->neighbours[i].city->getName(), to) == 0)
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
                static char cityName[CITY_NAME_BUFFER];
                strcpy_s(cityName, getCityName(j, i));

                if (!cities.containsKey(cityName)) {
                    //std::cout << "74 | " << cityName << std::endl;
                    cities.putValue(cityName, new City(cityName, j, i));
                    //std::cout << "77 | Put " << cityName << " to cities\n";
                }
                else if (visited[i][j]) {

                    for (int k = 0; k < height; k++) {
                        for (int m = 0; m < width; m++) {


                            visited[k][m] = false;
                        }

                    }
                }
                //std::fill(&visited[0][0], &visited[0][0] + height * width, false);


                if (cities.containsKey(cityName)) {
                    lookForNeighbours(cityName);
                }
            }
        }
    }
}

void CitiesGraph::lookForNeighbours(char* cityName)
{
    //static char cityName[CITY_NAME_BUFFER];
    //strcpy_s(cityName2, cityName);
    static PrioritySpot queue;
    //std::cout << "97 | " << cityName << std::endl;
    int startCityPosX = cities[cityName]->getPosX();
    int startCityPosY = cities[cityName]->getPosY();

    queue.insert(spot(startCityPosX, startCityPosY));
    //if (width == 2048)    std::cout << cityName << std::endl;
    while (!queue.empty()) {
        bool endOfSearch = false;
        spot current = queue.extractMin();

        if (visited[current.y][current.x] && map[current.y][current.x] != '*') {
            continue;
        }

        if (map[current.y][current.x] == '*' && !(current.x == startCityPosX && current.y == startCityPosY)) {
            //static char neighbourCityName[CITY_NAME_BUFFER];
            // WARN | cityName � neighbourCityName - ���� ���������
            char* neighbourCityName = getCityName(current.x, current.y);
            //strcpy_s(neighbourCityName, getCityName(current.x, current.y));

            if (!cities.containsKey(neighbourCityName)) {
                cities.putValue(neighbourCityName, new City(neighbourCityName, current.x, current.y));
                //std::cout << "116 | Put " << neighbourCityName << " to cities\n";
            }


            for (int k = 0; k < cities[cityName]->neighbours.GetSize(); k++) {

                if (strcmp(cities[cityName]->neighbours[k].city->getName(), neighbourCityName) == 0 &&
                    (cities[cityName]->neighbours[k].distance > current.distance)
                    ) {
                    cities[cityName]->neighbours[k].distance = current.distance;
                    endOfSearch = true;
                    break;
                }
                else if (strcmp(cities[cityName]->neighbours[k].city->getName(), neighbourCityName) == 0) {
                    endOfSearch = true;
                    break;
                }
            }

            if (endOfSearch) {
                continue;
            }

            // Add new neighbour
            AnotherCity newNeighbour(current.distance, cities[neighbourCityName]);
            cities[cityName]->neighbours.push_back(newNeighbour);
            //std::cout << "\n142 | Add " << neighbourCityName << " to " << cityName << std::endl;

        }

        else if (map[current.y][current.x] == '#' || current.x == startCityPosX && current.y == startCityPosY) {

            //visited[current.y][current.x] = true;
            continueLookinfForNeighbour(queue, current);
        }
        visited[current.y][current.x] = true;
    }
}


void CitiesGraph::continueLookinfForNeighbour(PrioritySpot& queue, spot& current)
{
    for (int n = -1; n < 2; n += 2) {
        if (current.x + n >= 0 && current.x + n < width
            && (map[current.y][current.x + n] == '#' || map[current.y][current.x + n] == '*')
            //&& !visited[current.y][current.x + n]
            ) {

            queue.insert(spot(current.x + n, current.y, current.distance + 1));
        }

        if (current.y + n >= 0 && current.y + n < height
            && (map[current.y + n][current.x] == '#' || map[current.y + n][current.x] == '*')
            //&& !visited[current.y + n][current.x]
            ) {

            queue.insert(spot(current.x, current.y + n, current.distance + 1));
        }
    }
}


void CitiesGraph::printCities()
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // City is found
            if (map[i][j] == '*') {
                char* cityName = getCityName(j, i);

                std::cout << "City: " << cities[cityName]->getName() << "(" << cities[cityName]->getPosX() << ", " << cities[cityName]->getPosY() << ")" << "\n\t";
                for (int j = 0; j < cities[cityName]->neighbours.GetSize(); j++) {
                    if (j == 0) {
                        std::cout << "Neighbours:\n\t\t";
                    }
                    std::cout << cities[cityName]->neighbours[j].city->getName() << "(" << cities[cityName]->neighbours[j].distance << ")\n";
                    if (j < cities[cityName]->neighbours.GetSize() - 1) {
                        std::cout << "\t\t";
                    }
                }
            }
        }
    }
}



CitiesGraph::~CitiesGraph()
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // City is found
            if (map[i][j] == '*') {
                char* cityName = getCityName(j, i);

                delete cities[cityName];
            }
        }
    }

    for (int i = 0; i < height; i++) {
        delete[] map[i];
        delete[] visited[i];
    }

    delete[] map;
    delete[] visited;
}


CitiesGraph::CitiesGraph(const CitiesGraph& other) : height(other.height), width(other.width)
{
    // Copy the map
    map = new char* [height];
    for (int i = 0; i < height; i++) {
        map[i] = new char[width];
        memcpy(map[i], other.map[i], width);
    }

    // Copy the visited array
    visited = new bool* [height];
    for (int i = 0; i < height; i++) {
        visited[i] = new bool[width];
        memcpy(visited[i], other.visited[i], width);
    }
}

CitiesGraph& CitiesGraph::operator=(const CitiesGraph& other)
{
    if (this != &other) // avoid self-assignment
    {
        // delete existing data
        for (int i = 0; i < height; i++) {
            delete[] map[i];
            delete[] visited[i];
        }
        delete[] map;
        delete[] visited;

        // copy data from other object
        height = other.height;
        width = other.width;
        cities = other.cities;

        // allocate new memory for map and visited arrays
        map = new char* [height];
        visited = new bool* [height];
        for (int i = 0; i < height; i++) {
            map[i] = new char[width];
            visited[i] = new bool[width];
            for (int j = 0; j < width; j++) {
                map[i][j] = other.map[i][j];
                visited[i][j] = other.visited[i][j];
            }
        }
    }
    return *this;
}