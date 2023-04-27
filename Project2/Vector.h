#pragma once
#include "Parameters.h"


template <typename T>
class Vector {
    T* data;
    int size;
    int allocated_size;
    void reallocate(int new_size);
    
public:
    Vector() = delete;
    Vector(int size = VECTOR_START_SIZE);
    Vector(const Vector<T>& other);
    ~Vector();
    
    Vector<T>& operator=(const Vector<T>& other);
    T& operator [] (int index) const;
    
    void push_back(const T& value);
    T pop_back();
    
    int GetSize() const;
    void clear();
    bool isEmpty() const;

    T& front();
    T& back();
};


template<typename T>
Vector<T>::Vector(int size)
    : data(nullptr), size(0), allocated_size(size) {}


template<typename T>
Vector<T>::~Vector()
{
    if (allocated_size > 0) {
        allocated_size = 0;
        delete[] data;
    }
}


template<typename T>
Vector<T>::Vector(const Vector<T>& other)
    : data(nullptr), size(other.size), allocated_size(other.allocated_size)
{
    if (allocated_size > 0) {
        data = new T[allocated_size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
}


template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    if (this != &other) {
        clear();
        
        if (other.size > 0) {
            data = new T[other.size];
            allocated_size = other.size;
            
            for (int i = 0; i < other.size; i++) {
                data[i] = other.data[i];
            }
            size = other.size;
        }
    }
    return *this;
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
    if (size > 0) {
        delete[] data;
    }
    data = new_data;
}


template<typename T>
void Vector<T>::push_back(const T& value)
{
    // If it is the first push_back (memory isn't allocated)
    if (allocated_size && data == nullptr) {
        data = new T[allocated_size];
    }
    if (size == allocated_size) {
        reallocate(2 * allocated_size);
    }
    data[size++] = value;
}

template<typename T>
T Vector<T>::pop_back()
{
    if (size < 1) {
        throw "Vector is empty";
    }
    
    T last_value = data[--size];
    if (size > VECTOR_START_SIZE && 4 * (size) <= allocated_size) {
        reallocate(allocated_size / 2);
    }
    return last_value;
}

template<typename T>
T& Vector<T>::operator[](int index) const
{
    return data[index];
}

template<typename T>
int Vector<T>::GetSize() const
{
    return this->size;
}

template<typename T>
void Vector<T>::clear()
{
    if (size > 0) {
        delete[] data;
    }
    size = 0;
    allocated_size = 0;
}

template<typename T>
inline bool Vector<T>::isEmpty() const
{
    return size < 1;
}

template<typename T>
inline T& Vector<T>::front()
{
    return data[0];
}

template<typename T>
inline T& Vector<T>::back()
{
    return data[size - 1];
}