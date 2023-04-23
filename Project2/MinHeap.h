#pragma once
#include "Parameters.h"

class MinHeap {
private:
    Vector<AnotherCity*> heap;
    int getParent(int i) { return (i - 1) / 2; }
    int getLeftChild(int i) { return 2 * i + 1; }
    int getRightChild(int i) { return 2 * i + 2; }

    void siftUp(int i) {
        while (i > 0 && (heap[i]->distance < heap[getParent(i)]->distance ||
            (heap[i]->distance == heap[getParent(i)]->distance && heap[i]->id < heap[getParent(i)]->id))) {
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

            if (left < heap.GetSize() && (heap[left]->distance < heap[minIndex]->distance ||
                (heap[left]->distance == heap[minIndex]->distance && heap[left]->id < heap[minIndex]->id))) {
                minIndex = left;
            }

            if (right < heap.GetSize() && (heap[right]->distance < heap[minIndex]->distance ||
                (heap[right]->distance == heap[minIndex]->distance && heap[right]->id < heap[minIndex]->id))) {
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
    MinHeap() : heap(VECTOR_START_SIZE) {}

    void insert(AnotherCity* value) {
        heap.push_back(value);
        siftUp(heap.GetSize() - 1);
    }
    AnotherCity* extractMin() {

        /*std::cout << "Heap: " << std::endl;
        for (int i = 0; i < heap.GetSize(); i++) {
            if (heap[i]) {
                std::cout << i << " " << heap[i]->distance << std::endl;
            }
        }*/

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
