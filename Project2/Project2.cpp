#include "Parameters.h"
//#include <chrono>
using namespace std;

int AnotherCity::idCounter = 0;
void readFlights(CitiesGraph& graph);
void readCommands(CitiesGraph& graph);

int main()
{
    int width, height;
    std::cin >> width >> height;

    //auto start_time = std::chrono::high_resolution_clock::now();
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
    /*auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "READ MAP Execution time: " << duration.count() << " milliseconds" << std::endl;

    auto start_time2 = std::chrono::high_resolution_clock::now();*/
    CitiesGraph graph(map, height, width);
    /*auto end_time2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time2 - start_time2);
    std::cout << "BUILD GRAPH Execution time: " << duration2.count() << " milliseconds" << std::endl;

    auto start_time3 = std::chrono::high_resolution_clock::now();*/
    readFlights(graph);
    //auto end_time3 = std::chrono::high_resolution_clock::now();
    //auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time3 - start_time3);
    //std::cout << "READ FLIGHTS Execution time: " << duration3.count() << " milliseconds" << std::endl;

    ////graph.printCities();

    //auto start_time4 = std::chrono::high_resolution_clock::now();
    readCommands(graph);
    /*auto end_time4 = std::chrono::high_resolution_clock::now();
    auto duration4 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time4 - start_time4);
    std::cout << "DO COMMANDS Execution time: " << duration4.count() << " milliseconds" << std::endl;*/

}


void readFlights(CitiesGraph& graph)
{
    int countOfFlights;
    char line[BUFFER_SIZE];

    do {
        std::fgets(line, BUFFER_SIZE, stdin);
    } while (line[0] == '\n');

    char* endptr = nullptr;
	// Convert string to int
    countOfFlights = std::strtol(line, &endptr, 10);

    char* p = endptr;
    char* from = nullptr, * to = nullptr;
    int time;

    for (int i = 0; i < countOfFlights; i++) {
        std::fgets(line, BUFFER_SIZE, stdin);
        p = line;

        from = p;
        // Look for the end of the first world
        while (*p != ' ') {
            ++p;
        }
        *p = '\0';

        
        to = ++p;
		// Look for the end of the second world
        while (*p != ' ') {
            ++p;
        }
        *p = '\0';
        
		// Convert string to int
		time = std::strtol(++p, &p, 10);

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