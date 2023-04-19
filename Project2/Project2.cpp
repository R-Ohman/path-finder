#include <iostream>
//#include "Vector.h"
#include "String.h"


template <typename T>
class Vector {
	T* data;
	int size;
	int allocated_size;
	void init();
	void reallocate(int new_size);
public:
	Vector() { init(); }
	~Vector() { delete[] data; }
	void push_back(T value);
	T pop_back();
	T& operator [] (int index) { return data[index]; }
	int GetSize() { return size; }
	void clear();
};


int main()
{
	int width, height;
	std::cin >> width >> height;

	char** map = new char* [height];
	
	for (int i = 0; i < height; i++) {
		map[i] = new char[width];
	}
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			char c;
			std::cin >> map[i][j];
		}
	}

	Vector<String> cities;
	
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (map[i][j] == '*') {
				String cityName;
				for (int k = -1; k < 2; k++) {
					for (int m = -1; m < 2; m++) {
						if (cityName.GetLength() > 0) {
							break;
						}
						if (j + m < 0 || j + m >= width || i + k < 0 || i + k >= height) {
							continue;
						}
						if (map[i + k][j + m] >= 'A' && map[i + k][j + m] <= 'Z') {
							int tmpX1 = j + m, tmpX2 = j + m + 1;
							// read the name to the left border
							while (tmpX1 >= 0 && map[i + k][tmpX1] >= 'A' && map[i + k][tmpX1] <= 'Z') {
								// warn | fixed | ошибка в Стринг при strcpy
								cityName.PushFront(map[i + k][tmpX1]);
								tmpX1--;
							}
							// read the name to the right border
							while (tmpX2 < width && map[i + k][tmpX2] >= 'A' && map[i + k][tmpX2] <= 'Z') {
								cityName += map[i + k][tmpX2];
								tmpX2++;
							}
							cities.push_back(cityName);
							break;
						}
					}
				}
			}
		}
	}
	
	for (int i = 0; i < cities.GetSize(); i++) {
		std::cout << cities[i] << std::endl;
	}
	
}


template<typename T>
void Vector<T>::init()
{
	size = 0;
	allocated_size = 1;
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
void Vector<T>::clear()
{
	delete[] data;
	init();
}
