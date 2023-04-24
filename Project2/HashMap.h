#pragma once
#include "Parameters.h"

template <typename T>
class HashMap {
private:
    struct Node {
        String key;
        T value;
        Node* next;
        Node(String k, T v) : key(k), value(v), next(nullptr) {}
    };

    Node** table;
    int table_size;
    int count;

    unsigned hash(String key);

public:
    HashMap();

    ~HashMap();

    void putValue(String key, T value);

    bool containsKey(String key);

    T getValue(String key);

    int getSize();

    T& operator [](String key);

};


template<typename T>
inline unsigned HashMap<T>::hash(String key)
{
    unsigned int hash = 0;
    for (size_t i = 0; i < key.GetLength(); i++) {
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
inline void HashMap<T>::putValue(String key, T value)
{
    int index = hash(key) % table_size;
    Node* current = table[index];
    while (current != nullptr) {
        if (current->key == key) {
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
inline bool HashMap<T>::containsKey(String key)
{
    int index = hash(key) % table_size;
    Node* current = table[index];
    while (current != nullptr) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
inline T HashMap<T>::getValue(String key)
{
    int index = hash(key) % table_size;
    Node* current = table[index];
    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return T();
}

template<typename T>
T& HashMap<T>::operator [](String key)
{
    try {
        int index = hash(key) % table_size;
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
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