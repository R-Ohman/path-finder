#pragma once

#include "Parameters.h"

template <typename T>
class Vector {
	T* data;
	int size;
	int allocated_size;
	void init();
	void reallocate(int new_size);
public:
	Vector();
	~Vector();
	void push_back(T value);
	T pop_back();
	T& operator [] (int index);
	int GetSize();
	void clear();
};


template<typename T>
Vector<T>::Vector()
{
	init();
}


template<typename T>
Vector<T>::~Vector()
{
	delete[] data;
}


template<typename T>
void Vector<T>::init()
{
	size = 0;
	allocated_size = VECTOR_START_SIZE;
	data = new T[allocated_size];
}


template<typename T>
void Vector<T>::reallocate(int new_size)
{
	allocated_size = new_size;
	T* new_data = new T[allocated_size];
	if (new_data != nullptr) {
		for (int i = 0; i < size; i++) {
			new_data[i] = data[i];
		}
	}
	delete[] data;
	data = new_data;
}


template<typename T>
void Vector<T>::push_back(T value)
{
	if (size == allocated_size) {
		reallocate(2 * allocated_size);
	}
	data[size++] = value;
}

template<typename T>
T Vector<T>::pop_back()
{
	T last_value = data[--size];
	if (4 * (size) <= allocated_size) {
		reallocate(allocated_size / 2);
	}
	return last_value;
}

template<typename T>
T& Vector<T>::operator[](int index)
{
	return data[index];
}

template<typename T>
int Vector<T>::GetSize()
{
	return this->size;
}

template<typename T>
void Vector<T>::clear()
{
	delete[] data;
	init();
}