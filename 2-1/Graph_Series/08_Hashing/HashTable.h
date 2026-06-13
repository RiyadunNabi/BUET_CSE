#pragma once
#include "RedBlackTree.h"
#include <iostream>
#include <string>
#include <vector>
#include "HashFunctions.h"

using namespace std;

enum HashChoice { HASH1 = 1, HASH2 = 2 };

enum SlotState { EMPTY, OCCUPIED, DELETED };

struct OA_Pair {
    string key;
    int value;
    SlotState state;
};

class HashTable {
  private:
    long long N;
    string strategy;
    int hash_choice;
    int S;
    long long collisions;

    vector<RedBlackTree *> table_chaining;
    vector<OA_Pair> table_open_addressing;
    
    long long primary_hash(string &key) {
        if (hash_choice == HASH1) return hash1(key,N);
        return hash2(key,N);
    }
    long long secondary_hash(string &key) {
        if (hash_choice == HASH1) return hash2(key,N);
        return hash1(key,N);
    }

  public:

    HashTable(int n_prime,string &strategy, int hash_func_choice = 1, int step_size = 3) {
        this->N = find_next_prime(n_prime);
        this->strategy = strategy;
        this->hash_choice = hash_func_choice;
        this->S = step_size;
        this->collisions = 0;

        if (strategy == "chaining") {
            table_chaining.resize(N, nullptr);
        } else {
            table_open_addressing.resize(N);
            for (int i = 0; i < N; ++i) {
                table_open_addressing[i].state = EMPTY;
            }
        }
    }

    ~HashTable() {
        if (strategy == "chaining") {
            for (auto &tree : table_chaining) {
                if (tree != nullptr) {
                    delete tree;
                }
            }
        }
    }

    void insert(string &key, int value) {
        if (strategy == "chaining") {
            long long index = primary_hash(key);
            if (table_chaining[index] == nullptr) {
                table_chaining[index] = new RedBlackTree();
            } else {
                collisions++;
            }
            table_chaining[index]->insert(key, value);
        } else { // Open Addressing
            long long i = 0;
            while (i < N) {
                long long index;
                if (strategy == "linear") {
                    index = (primary_hash(key) + i * S) % N;
                } else { // Double Hashing
                    index = (primary_hash(key) + i * secondary_hash(key)) % N;
                }

                if (table_open_addressing[index].state == EMPTY || table_open_addressing[index].state == DELETED) {
                    table_open_addressing[index] = {key, value, OCCUPIED};
                    return;
                }
                
                if (table_open_addressing[index].key == key) {
                    return;
                }

                collisions++;
                i++;
            }
        }
    }

    pair<int, int> search(string &key) {
        int probes = 0;
        if (strategy == "chaining") {
            long long index = primary_hash(key);
            probes = 1; // access the bucket
            if (table_chaining[index] != nullptr) {
                Node* result = table_chaining[index]->search(key);
                if (result != nullptr) {
                    return {result->value, probes};
                }
            }
            return {-1, probes};
        } else { // OpenAddressing
            long long i = 0;
            while (i < N) {
                probes++;
                long long index;
                if (strategy == "linear") {
                    index = (primary_hash(key) + i * S) % N;
                } else { // Double 
                    index = (primary_hash(key) + i * secondary_hash(key)) % N;
                }

                if (table_open_addressing[index].state == EMPTY) {
                    return {-1, probes};
                }
                if (table_open_addressing[index].state == OCCUPIED && table_open_addressing[index].key == key) {
                    return {table_open_addressing[index].value, probes};
                }
                i++;
            }
        }
        return {-1, probes};
    }

    void remove(string &key) {
        if (strategy == "chaining") {
            long long index = primary_hash(key);
            if (table_chaining[index] != nullptr) {
                table_chaining[index]->deleteNode(key);
            }
        } else { // Open 
            long long i = 0;
            while (i < N) {
                long long index;
                if (strategy == "linear") {
                    index = (primary_hash(key) + i * S) % N;
                } else { // Double 
                    index = (primary_hash(key) + i * secondary_hash(key)) % N;
                }

                if (table_open_addressing[index].state == EMPTY) {
                    return;
                }

                if (table_open_addressing[index].state == OCCUPIED && table_open_addressing[index].key == key) {
                    table_open_addressing[index].state = DELETED;
                    return;
                }
                i++;
            }
        }
    }

    long long getCollisions() {
        return collisions;
    }
};
