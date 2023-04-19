#include "Vector.h"

template<typename T>
void Vector<T>::reallocate(int new_size)
{
	allocated_size = new_size;
	T* new_data = new T[allocated_size];
	if (new_data != 0) memcpy(new_data, data, size * sizeof(T));
	delete[] data;
	data = new_data;
}

template<typename T>
Vector<T>::Vector()
{
	this->init();
}

template<typename T>
void Vector<T>::init()
{
	size = 0;
	allocated_size = 100;
	data = new T[allocated_size];
}

template<typename T>
Vector<T>::~Vector()
{
	delete[] data;
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
