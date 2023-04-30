#pragma once
#include "Parameters.h"

class MinHeap {
private:
    Vector<AnotherCity*> heap;
    
    static int getParent(int i) { return (i - 1) / 2; }
    static int getLeftChild(int i) { return 2 * i + 1; }
    static int getRightChild(int i) { return 2 * i + 2; }

    void siftUp(int i)
    {
		// While we haven't reached the root and there is a smaller element than the current one -> swap 
        while (i > 0 && (heap[i]->distance < heap[getParent(i)]->distance ||
            (heap[i]->distance == heap[getParent(i)]->distance && heap[i]->id < heap[getParent(i)]->id))
            ) {
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

            if (left < heap.GetSize() && (heap[left]->distance < heap[minIndex]->distance ||
                (heap[left]->distance == heap[minIndex]->distance && heap[left]->id < heap[minIndex]->id))
                ) {
                minIndex = left;
            }

            if (right < heap.GetSize() && (heap[right]->distance < heap[minIndex]->distance ||
                (heap[right]->distance == heap[minIndex]->distance && heap[right]->id < heap[minIndex]->id))
                ) {
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
    MinHeap() : heap(VECTOR_START_SIZE) {}

    void insert(AnotherCity* value)
    {
        heap.push_back(value);
        siftUp(heap.GetSize() - 1);
    }

	// Returns the root of the heap, removes it and restores the heap
    AnotherCity* extractMin()
    {
        AnotherCity* root = heap.front();
        std::swap(heap.front(), heap.back());
        heap.pop_back();
        siftDown();

        return root;
    }

    bool empty() {
        return heap.isEmpty();
    }
};