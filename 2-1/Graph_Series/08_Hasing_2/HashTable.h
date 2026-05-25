#pragma once
#include "HashFunctions.h"
#include "RedBlackTree.h"
#include <vector>
#include <string>


class HashTable {
    private:
    unsigned int table_size;
    vector<RedBlackTree> table;
    unsigned int current_id;
    
    public:
    HashTable(unsigned int size) : table_size(size), table(size), current_id(1) {}
    
    // Insert: returns value if new, 0 if duplicate
    unsigned int insert(const string &key) {
        unsigned int idx = Hash1(key, table_size); // or Hash2
        int val;
        if (table[idx].getValue(key, val))
        return 0; // duplicate
        table[idx].insert(key, current_id);
        return current_id++;
    }
    
    // Search: returns value if found, 0 if not
    unsigned int search(const string &key) {
        unsigned int idx = Hash1(key, table_size);
        int val;
        if (table[idx].getValue(key, val))
        return val;
        return 0;
    }
    
    // Delete: returns true if deleted, false if not found
    bool remove(const string &key) {
        unsigned int idx = Hash1(key, table_size);
        return table[idx].deleteNode(key);
    }
};
//====================================================================================
struct LinearEntry {
    string key;
    int value;
    bool occupied;
    bool deleted;

    LinearEntry() : key(""), value(0), occupied(false), deleted(false) {}
};

class LinearProbingHashTable {
private:
    unsigned int table_size;
    vector<LinearEntry> table;
    unsigned int current_id;
    unsigned int S; // Step size
    
    public:
    LinearProbingHashTable(unsigned int size, unsigned int step) :
    table_size(size), table(size), current_id(1), S(step) {}
    
    // Insert: returns value if new, 0 if duplicate
    unsigned int insert(const string& key) {
        unsigned int hash = Hash1(key, table_size); // or Hash2
        unsigned int idx;
        for (unsigned int i = 0; i < table_size; ++i) {
            idx = (hash + i * S) % table_size;
            if (!table[idx].occupied || table[idx].deleted) {
                // Insert new
                table[idx].key = key;
                table[idx].value = current_id;
                table[idx].occupied = true;
                table[idx].deleted = false;
                return current_id++;
            } else if (table[idx].key == key && !table[idx].deleted) {
                // Duplicate found
                return 0;
            }
            // Otherwise, keep probing
        }
        throw overflow_error("Hash table is full!");
    }

    // Search: returns value if found, 0 if not
    unsigned int search(const string& key) {
        unsigned int hash = Hash1(key, table_size); // or Hash2
        unsigned int idx;
        for (unsigned int i = 0; i < table_size; ++i) {
            idx = (hash + i * S) % table_size;
            if (!table[idx].occupied && !table[idx].deleted)
                return 0; // Not found and no more possible
            if (table[idx].occupied && table[idx].key == key && !table[idx].deleted)
                return table[idx].value; // Found
            // Else, keep probing
        }
        return 0; // Not found after full loop
    }

    // Delete: returns true if deleted, false if not found
    bool remove(const string& key) {
        unsigned int hash = Hash1(key, table_size); // or Hash2
        unsigned int idx;
        for (unsigned int i = 0; i < table_size; ++i) {
            idx = (hash + i * S) % table_size;
            if (!table[idx].occupied && !table[idx].deleted)
                return false; // Not found
            if (table[idx].occupied && table[idx].key == key && !table[idx].deleted) {
                table[idx].deleted = true;
                return true; // Deleted
            }
        }
        return false;
    }
};

//==================================================================================
struct DoubleHashEntry {
    string key;
    int value;
    bool occupied;
    bool deleted;

    DoubleHashEntry() : key(""), value(0), occupied(false), deleted(false) {}
};

class DoubleHashingHashTable {
private:
    unsigned int table_size;
    vector<DoubleHashEntry> table;
    unsigned int current_id;

public:
    DoubleHashingHashTable(unsigned int size)
        : table_size(size), table(size), current_id(1) {}
        
    unsigned int insert(const string& key) {
        unsigned int hash_a = Hash1(key, table_size);
        unsigned int hash_b = Hash2(key, table_size); // Hash2 never returns 0

        unsigned int idx;
        for (unsigned int i = 0; i < table_size; ++i) {
            idx = (hash_a + i * hash_b) % table_size;
            if (!table[idx].occupied || table[idx].deleted) {
                // Insert new
                table[idx].key = key;
                table[idx].value = current_id;
                table[idx].occupied = true;
                table[idx].deleted = false;
                return current_id++;
            } else if (table[idx].key == key && !table[idx].deleted) {
                // Duplicate
                return 0;
            }
        }
        throw overflow_error("Hash table is full!");
    }

    // Search: returns value if found, 0 if not
    unsigned int search(const string& key) {
        unsigned int hash_a = Hash1(key, table_size);
        unsigned int hash_b = Hash2(key, table_size);

        unsigned int idx;
        for (unsigned int i = 0; i < table_size; ++i) {
            idx = (hash_a + i * hash_b) % table_size;
            if (!table[idx].occupied && !table[idx].deleted)
                return 0;
            if (table[idx].occupied && table[idx].key == key && !table[idx].deleted)
                return table[idx].value;
        }
        return 0;
    }

    // Delete: returns true if deleted, false if not found
    bool remove(const string& key) {
        unsigned int hash_a = Hash1(key, table_size);
        unsigned int hash_b = Hash2(key, table_size);

        unsigned int idx;
        for (unsigned int i = 0; i < table_size; ++i) {
            idx = (hash_a + i * hash_b) % table_size;
            if (!table[idx].occupied && !table[idx].deleted)
                return false;
            if (table[idx].occupied && table[idx].key == key && !table[idx].deleted) {
                table[idx].deleted = true;
                return true;
            }
        }
        return false;
    }
};

// #include <iostream>
// #include <vector>
// #include <set>
// #include <string>
// #include "HashFunctions.h"

// using namespace std;

// class HashTable {
// private:
//     unsigned int table_size;
//     vector<set<pair<string, int>>> table; // each slot: a BST (balanced)
//     unsigned int current_id; // unique value for each new insertion

// public:
//     HashTable(unsigned int size) : table_size(size), table(size), current_id(1) {}

//     // Insert word, returns the assigned value if new, or 0 if duplicate
//     unsigned int insert(const string& key) {
//         unsigned int idx = Hash1(key, table_size); // use Hash1 for now
//         for (const auto& p : table[idx]) {
//             if (p.first == key)
//                 return 0; // duplicate
//         }
//         table[idx].insert({key, current_id});
//         return current_id++;
//     }

//     // Search for word, returns its assigned value or 0 if not found
//     unsigned int search(const string& key) {
//         unsigned int idx = Hash1(key, table_size);
//         for (const auto& p : table[idx]) {
//             if (p.first == key)
//                 return p.second;
//         }
//         return 0; // not found
//     }

//     // Delete a word, returns true if deleted, false if not found
//     bool remove(const string& key) {
//         unsigned int idx = Hash1(key, table_size);
//         for (auto it = table[idx].begin(); it != table[idx].end(); ++it) {
//             if (it->first == key) {
//                 table[idx].erase(it);
//                 return true;
//             }
//         }
//         return false; // not found
//     }

//     // For performance stats: count collisions (for insertions)
//     unsigned int count_collisions(const string& key) {
//         unsigned int idx = Hash1(key, table_size);
//         return table[idx].size();
//     }
// };
