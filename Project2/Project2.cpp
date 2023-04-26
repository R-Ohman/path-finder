#include "Parameters.h"

int AnotherCity::idCounter = 0;
void readFlights(CitiesGraph& graph);
void readCommands(CitiesGraph& graph);

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
            
            map[i][j] = getchar();
            if (map[i][j] == '\n') {
                map[i][j] = getchar();
            }
        }
    }

    CitiesGraph graph(map, height, width);

    readFlights(graph);

    //graph.printCities();

    readCommands(graph);
}


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

        graph.dijkstra(from, to, typeOfSearch);
    }
}