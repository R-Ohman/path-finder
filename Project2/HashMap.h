#pragma once
#include "Parameters.h"

template <typename T>
class HashMap {
private:
    struct Node {
        char key[CITY_NAME_BUFFER];
        T value;
        Node* next;
        Node(const char* k, const T& v) : value(v), next(nullptr) {
			strcpy_s(key, k);
        }
    };

    Node** table;
    int table_size;     // HASHMAP_SIZE
	int count;          // number of elements in the table

    static unsigned hash(const char* key);

public:
    HashMap();

    ~HashMap();
    
    void putValue(char* key, const T& value);
    bool containsKey(char* key) const;
    T getValue(char* key) const;
    int getSize() const;

    T& operator [](const char* key) const;

    Node** getTable() const {
        return table;
    }

    int getTableSize() const {
        return table_size;
    }

    class Iterator;

    Iterator begin() const {
        for (int i = 0; i < table_size; i++) {
            if (table[i] != nullptr) {
                return Iterator(&table[i], table[i], table, table_size);
            }
        }
        return end();
    }

    Iterator end() const {
        return Iterator(nullptr, nullptr, table, table_size);
    }
};


template<typename T>
inline unsigned HashMap<T>::hash(const char* key)
{
    unsigned int hash = 0;
    const char* p = key;
    while (*p) {
        hash = hash * 31 + *p++;
    }
    return hash;
}


template<typename T>
inline HashMap<T>::HashMap() : table_size(HASHMAP_SIZE), count(0)
{
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
inline void HashMap<T>::putValue(char* key, const T& value)
{
    int index = hash(key) % table_size;
    Node* current = table[index];
    
    while (current != nullptr) {
		// If key already exists, update value
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    }
	// If key doesn't exist, create new node
    Node* new_node = new Node(key, value);
    new_node->next = table[index];
    table[index] = new_node;
    count++;
}


template<typename T>
inline bool HashMap<T>::containsKey(char* key) const
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
inline T HashMap<T>::getValue(char* key) const
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
T& HashMap<T>::operator [](const char* key) const
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
		// If key doesn't exist, create new node
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
inline int HashMap<T>::getSize() const
{
    return this->count;
}


template <typename T>
class HashMap<T>::Iterator {
private:
    Node** current_bucket;
    Node* current_node;
    Node** table;
    int table_size;

public:
    Iterator(Node** bucket, Node* node, Node** t, int ts) : current_bucket(bucket), current_node(node), table(t), table_size(ts) {}
    Iterator& operator++() {
        if (current_node->next != nullptr) {
            current_node = current_node->next;
        }
        else {
            int bucket_index = current_bucket - this->table;
            while (++bucket_index < this->table_size && this->table[bucket_index] == nullptr);
            if (bucket_index < this->table_size) {
                current_bucket = &this->table[bucket_index];
                current_node = *current_bucket;
            }
            else {
                current_bucket = nullptr;
                current_node = nullptr;
            }
        }
        return *this;
    }

    T& operator*() const {
        return current_node->value;
    }

    bool operator==(const Iterator& other) const {
        return current_node == other.current_node;
    }

    bool operator!=(const Iterator& other) const {
        return !(*this == other);
    }
};