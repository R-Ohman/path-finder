#pragma once
#include "Parameters.h"


template <typename T>
class Vector {

	struct Node {
		T* data;
		int occupiedCells;
		Node* next;
	};
	Node* head;
	Node* tail;
	int size;
	int allocated_size;
	//void reallocate(int new_size);
public:
	Vector() = delete;
	Vector(int size = VECTOR_START_SIZE);
	Vector(const Vector<T>& other);
	~Vector();
	Vector<T>& operator=(const Vector<T>& other);
	void push_back(T value);
	T pop_back();
	T& operator [] (int index);
	int GetSize();
	void clear();
	bool isEmpty();

	T& front();
	T& back();
};


template<typename T>
Vector<T>::Vector(int size) : allocated_size(size), size(0)
{
	if (allocated_size) {
		head = new Node;
		head->data = new T[allocated_size];
		tail = head;
		head->occupiedCells = 0;
		tail->next = nullptr;
	}
}


template<typename T>
Vector<T>::~Vector()
{
	if (allocated_size > 0) {
		Node* current = head;
		while (current != nullptr) {
			Node* next = current->next;
			delete[] current->data;
			delete current;
			current = next;
		}
	}
}


template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	if (allocated_size > 0) {
		head = new Node;
		head->data = new T[allocated_size];
		tail = head;
		head->occupiedCells = 0;
		tail->occupiedCells = 0;
		tail->next = nullptr;
		Node* current = other.head;
		while (current != nullptr) {
			for (int i = 0; i < current->occupiedCells; i++) {
				push_back(current->data[i]);
			}
			current = current->next;
		}
	}

}


template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other) {
		clear();
		if (other.size > 0) {
			head = new Node;
			head->data = new T[VECTOR_START_SIZE];
			tail = head;
			head->occupiedCells = 0;
			tail->occupiedCells = 0;
			tail->next = nullptr;
			Node* current = other.head;
			while (current != nullptr) {
				for (int i = 0; i < current->occupiedCells; i++) {
					push_back(current->data[i]);
				}
				current = current->next;
			}

			size = other.size;
		}
	}
	return *this;

}


//template<typename T>
//void Vector<T>::reallocate(int new_size)
//{
//	allocated_size = new_size;
//	T* new_data = new T[allocated_size];
//	if (new_data != nullptr) {
//		for (int i = 0; i < size; i++) {
//			new_data[i] = data[i];
//		}
//	}
//	if (size > 0) {
//		delete[] data;
//	}
//	data = new_data;
//}


template<typename T>
void Vector<T>::push_back(T value)
{
	if (tail->occupiedCells == VECTOR_START_SIZE) {
		allocated_size += VECTOR_START_SIZE;
		Node* new_node = new Node;
		new_node->data = new T[VECTOR_START_SIZE];
		new_node->next = nullptr;
		tail->next = new_node;
		tail = new_node;
		tail->occupiedCells = 0;
	}
	tail->data[tail->occupiedCells] = value;
	tail->occupiedCells++;
	size++;
}

template<typename T>
T Vector<T>::pop_back()
{
	if (size < 1 || head == nullptr) {
		throw "Vector is empty";
	}
	
	T last_value = tail->data[tail->occupiedCells - 1];
	if (tail->occupiedCells > 1) {
		tail->occupiedCells--;
	}
	else {
		Node* current = head;
		while (current->next != tail) {
			current = current->next;
		}
		delete[] tail->data;
		delete tail;
		allocated_size -= VECTOR_START_SIZE;
		tail = current;
		tail->occupiedCells = 0;
		tail->next = nullptr;
	}
	size--;
	return last_value;
}

template<typename T>
T& Vector<T>::operator[](int index)
{
	Node* current = head;
	while (current != nullptr) {
		if (index < current->occupiedCells) {
			return current->data[index];
		}
		index -= VECTOR_START_SIZE;
		current = current->next;
	}
	throw "Index out of bounds";
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
		Node* current = head;
		while (current != nullptr) {
			Node* next = current->next;
			//delete[] current->data;
			delete current;
			current = next;
		}
	}
	size = 0;
	allocated_size = VECTOR_START_SIZE;
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
	return tail->data[tail->occupiedCells - 1];
}
