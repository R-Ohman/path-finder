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
			// WARN
			while (i > 0 && heap[i].distance < heap[getParent(i)].distance) {
				std::swap(heap[i], heap[getParent(i)]);
				i = getParent(i);
			}
		}
		
		void siftDown() {
			int i = 0;
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
		PrioritySpot() : heap(VECTOR_BLOCK_SIZE) {}

		void insert(spot value) {
			heap.push_back(value);
			/*std::cout << "BEFORE siftUp(): value (" << value.x << ", " << value.y << ")\n\t";
			std::cout << "Size: " << heap.GetSize() << " | Allocated size: " << heap.allocated_size << " |\n";
			std::cout << "\tHeap:\n";
			for (int i = 0; i < heap.GetSize(); i++) {
				std::cout << "\t\t[" << heap[i].x << ", " << heap[i].y << ")\n";
			}*/
			siftUp(heap.GetSize() - 1);

			/*std::cout << "AFTER siftUp():\n\t";
			std::cout << "Size: " << heap.GetSize() << " | Allocated size: " << heap.allocated_size << " |\n";
			std::cout << "\tHeap:\n";
			for (int i = 0; i < heap.GetSize(); i++) {
				std::cout << "\t\t[" << heap[i].x << ", " << heap[i].y << ")\n";
			}*/
		}
		spot extractMin() {

			/*if (heap.GetSize() >= 8) {
				std::cout << "Flag";
			}*/
			spot root = heap.front();
			

			/*std::cout << "BEFORE extractMin():\n\t";
			std::cout << "Size: " << heap.GetSize() << " | Allocated size: " << heap.allocated_size << " | Front[" << root.x << ", " << root.y << ")\n";
			std::cout << "\tHeap:\n";
			for (int i = 0; i < heap.GetSize(); i++) {
				std::cout << "\t\t[" << heap[i].x << ", " << heap[i].y << ")\n";
			}*/
			
			std::swap(heap.front(), heap.back());
			heap.pop_back();
			siftDown();

			/*std::cout << "AFTER extractMin():\n\t";
			std::cout << "Size: " << heap.GetSize() << " | Allocated size: " << heap.allocated_size << " | Front[" << root.x << ", " << root.y << ")\n";
			std::cout << "\tHeap:\n";
			for (int i = 0; i < heap.GetSize(); i++) {
				std::cout << "\t\t[" << heap[i].x << ", " << heap[i].y << ")\n";
			}*/
			return root;
		}
		bool empty() {
			return heap.isEmpty();
		}
	};
	
	char** map;
	bool** visited;
	int height, width;

	char* getCityName(int x, int y);
	
	void getCities();
	void lookForNeighbours(char* cityName);
	void continueLookinfForNeighbour(PrioritySpot& queue, spot& current);
	
public:
	CitiesGraph(char** map, int h, int w);
	
	HashMap<City*> cities;
	
	void addNeighbour(char* from, char* to, int distance);
	
	void printCities();
	
	CitiesGraph(const CitiesGraph& other);
	CitiesGraph& operator=(const CitiesGraph& other);
	~CitiesGraph();
};

