#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>


template <typename T>
class Vector {
private:
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