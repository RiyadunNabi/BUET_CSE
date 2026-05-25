#include <string>
using namespace std;

// Hash1: Polynomial rolling hash
unsigned int Hash1(const string &key, unsigned int table_size) {
    unsigned long long hash = 0;
    unsigned long long p = 31;
    unsigned long long power = 1;
    for (char c : key) {
        hash = (hash + (c - 'a' + 1) * power) % table_size;
        power = (power * p) % table_size;
    }
    return hash % table_size;
}

// Hash2: Weighted sum hash
unsigned int Hash2(const string &key, unsigned int table_size) {
    unsigned long long hash = 0;
    unsigned long long p = 37;
    for (int i = 0; i < key.size(); ++i) {
        hash = (hash + (key[i] - 'a' + 1) * (i + 1) * p) % table_size;
    }
    // To avoid returning 0 (important for double hashing)
    return (hash % (table_size - 1)) + 1;
}
