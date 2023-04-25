#pragma once
#include "Parameters.h"


template <typename T>
class Vector {

    //T* data;

    
    int size;
    int allocated_size;
    void reallocate(int new_size);


    struct Block {
        T* data;
        int occupiedSize;
        Block* next;
        Block() : data(new T[VECTOR_START_SIZE]), occupiedSize(0), next(nullptr) {}
    };

    Block* head;
    Block* tail;
    
public:
    Vector() = delete;
    Vector(int size = VECTOR_START_SIZE);
    Vector(const Vector<T>& other);
    ~Vector();
    Vector<T>& operator=(const Vector<T>& other);
    void push_back(T value);
    T pop_back();
    T& operator [] (int index);
    const T& operator[](int index) const;
    int GetSize();
    void clear();
    bool isEmpty();

    T& front();
    T& back();
};


template<typename T>
Vector<T>::Vector(int size) : allocated_size(size), size(0), head(nullptr), tail(nullptr)
{
}


template<typename T>
Vector<T>::~Vector()
{
    if (allocated_size > 0) {
		Block* current = head;
        while (current != nullptr) {
            Block* temp = current;
            current = current->next;
            delete[] temp->data;
            delete temp;
        }
    }
}


template<typename T>
Vector<T>::Vector(const Vector<T>& other) : head(nullptr), tail(nullptr), size(0), allocated_size(0)
{
    Block* current = other.head;
    while (current != nullptr) {
        for (int i = 0; i < current->occupiedSize; i++) {
            push_back(current->data[i]);
        }
        current = current->next;
    }
}



template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    if (this != &other) {
        clear();
        for (int i = 0; i < other.size; i++) {
            push_back(other[i]);
        }
    }
    return *this;
}

template<typename T>
const T& Vector<T>::operator[](int index) const
{
    Block* current = head;
    int block_index = index / VECTOR_BLOCK_SIZE;
    int offset = index % VECTOR_BLOCK_SIZE;
    for (int i = 0; i < block_index; i++) {
        current = current->next;
    }
    return current->data[offset];
}



template<typename T>
void Vector<T>::reallocate(int new_size)
{
	//std::cout << "reallocate " << new_size << "\n";
    if (new_size > VECTOR_BLOCK_SIZE) {
		tail->next = new Block();
		tail = tail->next;
		allocated_size += VECTOR_START_SIZE;
    //    std::cout << "new Block\n";
    }
    else {
        allocated_size += new_size / 2;
        T* new_data = new T[new_size];
        if (new_data != nullptr) {
			for (int i = 0; i < tail->occupiedSize; i++) {
				new_data[i] = tail->data[i];
			}
        }
        if (tail->occupiedSize > 0) {
            delete[] tail->data;
        }
        tail->data = new_data;
    }
    
}


template<typename T>
void Vector<T>::push_back(T value)
{
    if (allocated_size && head == nullptr) {
        head = new Block;
		allocated_size = VECTOR_START_SIZE;
		tail = head;
    }
    if (tail->occupiedSize == allocated_size % VECTOR_BLOCK_SIZE) {
        reallocate(2 * tail->occupiedSize);
    }
	size++;
    tail->data[tail->occupiedSize++] = value;


}

template<typename T>
T Vector<T>::pop_back()
{
    if (size < 1) {
        throw "Vector is empty";
    }
    T last_value = tail->data[--tail->occupiedSize];
    size--;
    if (tail != head && tail->occupiedSize == 0) {
        Block* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        current->next = nullptr;
        delete tail;
        tail = current;
		allocated_size -= VECTOR_START_SIZE;
    }
    return last_value;
}

template<typename T>
T& Vector<T>::operator[](int index)
{
    Block* current = head;
    while (index >= VECTOR_BLOCK_SIZE) {
		current = current->next;
		index -= VECTOR_BLOCK_SIZE;
    }
	return current->data[index];
}

template<typename T>
int Vector<T>::GetSize()
{
    return this->size;
}

template<typename T>
void Vector<T>::clear()
{
	if (allocated_size > 0) {
		Block* current = head;
		while (current != nullptr) {
			Block* temp = current;
			current = current->next;
			delete[] temp->data;
			delete temp;
		}
	}
	head = nullptr;
	tail = nullptr;
}

template<typename T>
inline bool Vector<T>::isEmpty()
{
    return size < 1;
}

template<typename T>
inline T& Vector<T>::front()
{
    return head->data[0];
}

template<typename T>
inline T& Vector<T>::back()
{
	return tail->data[tail->occupiedSize - 1];
}