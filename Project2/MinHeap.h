#pragma once
#include "Parameters.h"

class MinHeap {
private:
    Vector<AnotherCity*> heap;
    int getParent(int i) { return (i - 1) / 2; }
    int getLeftChild(int i) { return 2 * i + 1; }
    int getRightChild(int i) { return 2 * i + 2; }
    void siftUp(int i) {
        while (i > 0 && heap[i]->distance < heap[getParent(i)]->distance) {
            std::swap(heap[i], heap[getParent(i)]);
            i = getParent(i);
        }
    }
    void siftDown(int i) {
        int minIndex = i;
        int left = getLeftChild(i);
        if (left < heap.GetSize() && heap[left]->distance < heap[minIndex]->distance) {
            minIndex = left;
        }
        int right = getRightChild(i);
        if (right < heap.GetSize() && heap[right]->distance < heap[minIndex]->distance) {
            minIndex = right;
        }
        if (i != minIndex) {
            std::swap(heap[i], heap[minIndex]);
            siftDown(minIndex);
        }
    }

public:
    MinHeap() : heap(VECTOR_START_SIZE) {}

    void insert(AnotherCity* value) {
        heap.push_back(value);
        siftUp(heap.GetSize() - 1);
    }
    AnotherCity* extractMin() {
        AnotherCity* root = heap.front();
        std::swap(heap.front(), heap.back());
        heap.pop_back();
        siftDown(0);
        return root;
    }
    bool empty() {
        return heap.isEmpty();
    }
};
