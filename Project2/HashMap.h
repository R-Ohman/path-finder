#pragma once
#include "Parameters.h"

template <typename T>
class HashMap {
private:
    struct Node {
        char key[CITY_NAME_BUFFER];
        T value;
        Node* next;
        Node(char* k, T v) : value(v), next(nullptr) {
            for (int i = 0; i < CITY_NAME_BUFFER; i++) {
				key[i] = k[i];
                if (k[i] == '\0') {
                    break;
                }
            }
        }
    };

    Node** table;
    int table_size;
    int count;

    unsigned hash(char* key);

public:
    HashMap();

    ~HashMap();

    void putValue(char* key, T value);

    bool containsKey(char* key);

    T getValue(char* key);

    int getSize();

    T& operator [](char* key);

};


template<typename T>
inline unsigned HashMap<T>::hash(char* key)
{
    unsigned int hash = 0;
    for (size_t i = 0;; i++) {
		if (key[i] == '\0') {
			break;
		}
        hash = hash * 31 + key[i];
    }
    return hash;
}

template<typename T>
inline HashMap<T>::HashMap()
{
    table_size = HASHMAP_SIZE;
    count = 0;
    table = new Node * [table_size]();
}

template<typename T>
inline HashMap<T>::~HashMap()
{
    for (int i = 0; i < table_size; i++) {
        Node* current = table[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}

template<typename T>
inline void HashMap<T>::putValue(char* key, T value)
{
//	std::cout << "putValue (" << key << ")\n";
    int index = hash(key) % table_size;
    Node* current = table[index];
    while (current != nullptr) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    Node* new_node = new Node(key, value);
    new_node->next = table[index];
    table[index] = new_node;
    count++;
}

template<typename T>
inline bool HashMap<T>::containsKey(char* key)
{
    int index = hash(key) % table_size;
    Node* current = table[index];
    while (current != nullptr) {
        if (strcmp(current->key, key) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
inline T HashMap<T>::getValue(char* key)
{
    int index = hash(key) % table_size;
    Node* current = table[index];
    while (current != nullptr) {
        if (strcmpt(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return T();
}

template<typename T>
T& HashMap<T>::operator [](char* key)
{
    try {
        int index = hash(key) % table_size;
        Node* current = table[index];
        while (current != nullptr) {
            if (strcmp(current->key, key) == 0) {
                return current->value;
            }
            current = current->next;
        }
        Node* new_node = new Node(key, T());
        new_node->next = table[index];
        table[index] = new_node;
        return new_node->value;
    }
    catch (const std::exception&) {
        throw std::exception("Key not found!");
    }
}

template<typename T>
inline int HashMap<T>::getSize()
{
    return count;
}