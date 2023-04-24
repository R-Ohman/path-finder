#pragma once
#include "Parameters.h"

class City;


class CitiesGraph
{
private:

	struct spot {
		int x, y, distance;
		spot(int x = -1, int y = -1, int distance = 0) : x(x), y(y), distance(distance) {}
	};
	
	class PrioritySpot {
	private:
		Vector<spot> heap;
		int getParent(int i) { return (i - 1) / 2; }
		int getLeftChild(int i) { return 2 * i + 1; }
		int getRightChild(int i) { return 2 * i + 2; }
		void siftUp(int i) {
			while (i > 0 && heap[i].distance < heap[getParent(i)].distance) {
				std::swap(heap[i], heap[getParent(i)]);
				i = getParent(i);
			}
		}
		void siftDown(int i) {
			int minIndex = i;
			int left = getLeftChild(i);
			if (left < heap.GetSize() && heap[left].distance < heap[minIndex].distance) {
				minIndex = left;
			}
			int right = getRightChild(i);
			if (right < heap.GetSize() && heap[right].distance < heap[minIndex].distance) {
				minIndex = right;
			}
			if (i != minIndex) {
				std::swap(heap[i], heap[minIndex]);
				siftDown(minIndex);
			}
		}

	public:
		PrioritySpot() : heap(VECTOR_START_SIZE) {}

		void insert(spot value) {
			heap.push_back(value);
			siftUp(heap.GetSize() - 1);
		}
		spot extractMin() {
			spot root = heap.front();
			std::swap(heap.front(), heap.back());
			heap.pop_back();
			siftDown(0);
			return root;
		}
		bool empty() {
			return heap.isEmpty();
		}
	};
	
	char** map;
	bool** visited;
	int height, width;

	
	void getCities();
	void lookForNeighbours(const String& cityName);
	void continueLookinfForNeighbour(PrioritySpot& queue, spot& current);
	
public:
	CitiesGraph(char** map, int h, int w);
	
	Vector<String> citiesNames;
	HashMap<City*> cities;
	
	void addNeighbour(const String& from, const String& to, int distance);
	
	void printCities();
	
	CitiesGraph(const CitiesGraph& other);
	CitiesGraph& operator=(const CitiesGraph& other);
	~CitiesGraph();
};

