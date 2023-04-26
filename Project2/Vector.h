#pragma once
#include "Parameters.h"


template <typename T>
class Vector {

    //T* data;

    
    int size;
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
    int allocated_size;
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
    /*if (index == size - 1) {
        std::cout << "Flag";
    }*/
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
	if (new_size < tail->occupiedSize) {
		return;
	}
	//std::cout << "reallocate " << new_size << "\n";
    if (new_size > VECTOR_BLOCK_SIZE) {
		tail->next = new Block;
		tail = tail->next;
		allocated_size += VECTOR_START_SIZE;
    //    std::cout << "new Block\n";
    }
    else {
        allocated_size -= allocated_size % VECTOR_BLOCK_SIZE;
		allocated_size += new_size;
		//std::cout << "new size " << allocated_size << "\n";
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
    /*if (size == 8 && allocated_size == 8) {
        std::cout << "Size 8 alloc 8 flag\n";
    }*/
    if (allocated_size && head == nullptr) {
        head = new Block;
		tail = head;
    }
  //  std::cout << "BEFORE Push back | Alloc size = " << allocated_size << " | Occupied size = " << tail->occupiedSize << "\n";
    if (tail->occupiedSize % VECTOR_BLOCK_SIZE == allocated_size % VECTOR_BLOCK_SIZE
        ) {
        reallocate(2 * tail->occupiedSize);
    }
	size++;
    tail->data[tail->occupiedSize++] = value;
  //  std::cout << "AFTER Push back | Alloc size = " << allocated_size << " | Occupied size = " << tail->occupiedSize << "\n";


}

template<typename T>
T Vector<T>::pop_back()
{
   // std::cout << "BEFORE Pop back | Alloc size = " << allocated_size << " | Occupied size = " << tail->occupiedSize << "\n";
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
	else if (size > VECTOR_START_SIZE && 4 * (tail->occupiedSize) <= allocated_size % VECTOR_BLOCK_SIZE) {
        reallocate((allocated_size % VECTOR_BLOCK_SIZE) / 2);
    }
   // std::cout << "AFTER Pop back | Alloc size = " << allocated_size << " | Occupied size = " << tail->occupiedSize << "\n";
    return last_value;
}

template<typename T>
T& Vector<T>::operator[](int index)
{
   /* if (size > VECTOR_BLOCK_SIZE && index == size - 1) {
        std::cout << "Flag";
    }*/
	Block* current = head;
	int block_index = index / VECTOR_BLOCK_SIZE;
	int offset = index % VECTOR_BLOCK_SIZE;
	for (int i = 0; i < block_index; i++) {
		current = current->next;
	}
	return current->data[offset];
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