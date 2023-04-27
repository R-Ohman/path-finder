#include "CitiesGraph.h"


// Min heap for spots
class CitiesGraph::PrioritySpot {
private:
    Vector<spot> heap;

    int getParent(int i) { return (i - 1) / 2; }
    int getLeftChild(int i) { return 2 * i + 1; }
    int getRightChild(int i) { return 2 * i + 2; }
    
    void siftUp(int i)
    {
        // While we haven't reached the root and there is a smaller element than the current one -> swap 
        while (i > 0 && heap[i].distance < heap[getParent(i)].distance) {
            std::swap(heap[i], heap[getParent(i)]);
            i = getParent(i);
        }
    }

    void siftDown()
    {
        int i = 0;
        // While the current element has at least one child -> swap with the smallest child
        while (i < heap.GetSize()) {
           
            int left = getLeftChild(i);
            int right = getRightChild(i);
            int minIndex = i;

            if (left < heap.GetSize() && (heap[left].distance < heap[minIndex].distance ||
                (heap[left].distance == heap[minIndex].distance && heap[left].x < heap[minIndex].x) ||
                (heap[left].distance == heap[minIndex].distance && heap[left].y < heap[minIndex].y))) {
                minIndex = left;
            }

            if (right < heap.GetSize() && (heap[right].distance < heap[minIndex].distance ||
                (heap[right].distance == heap[minIndex].distance && heap[right].x < heap[minIndex].x) ||
                (heap[right].distance == heap[minIndex].distance && heap[right].y < heap[minIndex].y))) {
                minIndex = right;
            }

            // If the current element is not the smallest -> swap with the smallest
            if (minIndex != i) {
                std::swap(heap[i], heap[minIndex]);
                i = minIndex;
            }
            else {
                break;
            }
        }
    }

public:
    PrioritySpot() : heap(VECTOR_START_SIZE) {}

    void insert(spot value)
    {
        heap.push_back(value);
        siftUp(heap.GetSize() - 1);
    }
    
    // Returns the root of the heap, removes it and restores the heap
    spot extractMin()
    {
        spot root = heap.front();
        std::swap(heap.front(), heap.back());
        heap.pop_back();
        siftDown();
        return root;
    }
    
    bool empty() {
        return heap.isEmpty();
    }
};


CitiesGraph::CitiesGraph(char** map, int h, int w) : map(map), height(h), width(w)
{
    visited = new bool* [height];
    for (int k = 0; k < height; k++) {
        visited[k] = new bool[width];
        for (int m = 0; m < width; m++) {
            visited[k][m] = false;
        }
    }
    // Create the graph
    getCities();

}


char* CitiesGraph::getCityName(int x, int y)
{
	// Check 4 neighbours
    for (int k = -1; k < 2; k++) {
        for (int m = -1; m < 2; m++) {
            if (x + m < 0 || x + m >= width || y + k < 0 || y + k >= height) {
                continue;
            }
            
            // One of the letters is found
            if (map[y + k][x + m] != '.' && map[y + k][x + m] != '#' && map[y + k][x + m] != '*') {
                int tmpX = x + m, i = 0;
                
                // Read the name to the left border
                while (tmpX >= 0 && map[y + k][tmpX] != '.' && map[y + k][tmpX] != '#' && map[y + k][tmpX] != '*') {
                    tmpX--;
                }
                static char buffer[CITY_NAME_BUFFER];
                // Read the name to the right border
                while (++tmpX < width && map[y + k][tmpX] != '.' && map[y + k][tmpX] != '#' && map[y + k][tmpX] != '*') {
                    buffer[i++] = map[y + k][tmpX];
                }
                buffer[i] = '\0';
                return buffer;
            }
        }
    }
    return nullptr;
}


void CitiesGraph::addNeighbour(char* from, char* to, int distance)
{
  //  for (int i = 0; i < cities[from]->neighbours.GetSize(); i++)
  //  {
		//// If the city is already a neighbour -> update the distance
  //      if (strcmp(cities[from]->neighbours[i].city->getName(), to) == 0)
  //      {
  //          if (cities[from]->neighbours[i].distance > distance)
  //          {
  //              cities[from]->neighbours[i].distance = distance;
  //          }
  //          return;
  //      }
  //  }
	// Add the new neighbour
    //AnotherCity newNeighbour(distance, cities[to]);
	static char last_from[CITY_NAME_BUFFER];
    static Vector<AnotherCity>* neighbours;
	if (strcmp(last_from, from) != 0) {
		strcpy_s(last_from, from);
		neighbours = &cities[from]->neighbours;
	} 
    neighbours->push_back(AnotherCity(distance, cities[to]));
    
    //cities[from]->neighbours.push_back(AnotherCity(distance, cities[to]));
}


void CitiesGraph::getCities()
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // City is found
            if (map[i][j] == '*') {
                static char cityName[CITY_NAME_BUFFER];
                strcpy_s(cityName, getCityName(j, i));

				// If it is the first time the city is found -> add it to the hashmap
                if (!cities.containsKey(cityName))
                {
                    cities.putValue(cityName, new City(cityName, j, i));
                }
                else if (visited[i][j]) {
					// If this city has already been visited -> reset the visited array
                    for (int k = 0; k < height; k++) {
                        for (int m = 0; m < width; m++) {
                            visited[k][m] = false;
                        }
                    }
                }
               
                lookForNeighbours(cityName);
            }
        }
    }
}

void CitiesGraph::lookForNeighbours(char* cityName)
{
    static PrioritySpot queue;
 
    int startCityPosX = cities[cityName]->getPosX();
    int startCityPosY = cities[cityName]->getPosY();

    queue.insert(spot(startCityPosX, startCityPosY));
    
    while (!queue.empty()) {
        spot current = queue.extractMin();

        if (visited[current.y][current.x] && map[current.y][current.x] != '*') {
            continue;
        }

		// If neighbour is found
        if (map[current.y][current.x] == '*' && !(current.x == startCityPosX && current.y == startCityPosY))
        {
            bool endOfSearch = false;
            char* neighbourCityName = getCityName(current.x, current.y);

			// If the city is not in the hashmap -> add it
            if (!cities.containsKey(neighbourCityName)) {
                cities.putValue(neighbourCityName, new City(neighbourCityName, current.x, current.y));
            }

            for (int k = 0; k < cities[cityName]->neighbours.GetSize(); k++) {

				// If the city is already a neighbour -> update the distance
                if (strcmp(cities[cityName]->neighbours[k].city->getName(), neighbourCityName) == 0 &&
                    (cities[cityName]->neighbours[k].distance > current.distance)
                    ) {
                    cities[cityName]->neighbours[k].distance = current.distance;
                    endOfSearch = true;
                    break;
                }
                else if (strcmp(cities[cityName]->neighbours[k].city->getName(), neighbourCityName) == 0) {
					// Don't add the neighbour if it is already in the list
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
        }
        else if (map[current.y][current.x] == '#' || current.x == startCityPosX && current.y == startCityPosY) {
			// If it is a road or the start city -> continue searching
            continueLookinfForNeighbour(queue, current);
        }
        visited[current.y][current.x] = true;
    }
}


void CitiesGraph::continueLookinfForNeighbour(PrioritySpot& queue, spot& current) const
{
	// Add roads and cities to the queue
    for (int n = -1; n < 2; n += 2) {
        if (current.x + n >= 0 && current.x + n < width
            && (map[current.y][current.x + n] == '#' || map[current.y][current.x + n] == '*')
            ) {
            queue.insert(spot(current.x + n, current.y, current.distance + 1));
        }

        if (current.y + n >= 0 && current.y + n < height
            && (map[current.y + n][current.x] == '#' || map[current.y + n][current.x] == '*')
            ) {
            queue.insert(spot(current.x, current.y + n, current.distance + 1));
        }
    }
}

void CitiesGraph::updateCity(AnotherCity* city, int distance, int visited, AnotherCity* prev)
{
	city->distance = distance;
	city->visited = visited;
	city->prev_city = prev;
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

void CitiesGraph::dijkstra(char* startCity, char* endCity, int typeOfSearch)
{
    if (strcmp(startCity, endCity) == 0) {
        std::cout << 0 << "\n";
        return;
    }
    
    static HashMap<AnotherCity* > graphCities;

    for (const auto& city : this->cities) {
		if (!graphCities.containsKey(city->getName())) {
			graphCities.putValue(city->getName(), new AnotherCity(INT_MAX, city));
		}
        else {
			graphCities[city->getName()]->distance = INT_MAX;
        }
		graphCities[city->getName()]->visited = false;
    }
	graphCities[startCity]->prev_city = nullptr;
	graphCities[startCity]->distance = 0;

    MinHeap queue;
    queue.insert(graphCities[startCity]);

    while (!queue.empty()) {
        AnotherCity* current = queue.extractMin();
        
        if (current->visited) {
            continue;
        }
        current->visited = true;
        
        for (int i = 0; i < current->city->neighbours.GetSize(); i++) {
			AnotherCity* neighbour = graphCities[current->city->neighbours[i].city->getName()];
            if (neighbour->distance > current->distance + current->city->neighbours[i].distance
                ) {
				// If we found a shorter path to the city -> update the distance
                //graphCities[current->city->neighbours[i].city->getName()]->distance = current->distance + current->city->neighbours[i].distance;
				// Update the queue with the new distance
                neighbour->distance = current->distance + current->city->neighbours[i].distance;
                neighbour->visited = false;
                neighbour->prev_city = current;
               // updateCity(neighbour, current->distance + current->city->neighbours[i].distance, false, current);
				//graphCities[current->city->neighbours[i].city->getName()]->visited = false;
                queue.insert(neighbour);
                //graphCities[current->city->neighbours[i].city->getName()]->prev_city = current;
             }
        }
    }
	// Print the distance (and the path)
    std::cout << graphCities[endCity]->distance;

    if (typeOfSearch == 1) {
        AnotherCity* current = graphCities[endCity];
        int ctr = 0;
        
        // Iterate through the path and add the cities to the vector
        Vector< char*> path(VECTOR_START_SIZE);
		while (current->prev_city != nullptr) {
            path.push_back(current->city->getName());
            current = current->prev_city;
        }
        path.push_back(current->city->getName());
        for (int i = path.GetSize() - 2; i > 0; i--) {
            std::cout << " " << path[i];
        }
    }
    std::cout << std::endl;
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