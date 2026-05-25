#include <iostream>
#include <vector>
#include "HashTable.h" 

using namespace std;

int main() {
    cout<<"======================================"<<endl;
    // Simple test for hash functions
    vector<string> words = {"coding", "algorithm", "coding", "datastr", "hashing"};
    
    unsigned int table_size = 10007;
    unsigned int step = 3; // or 5
    LinearProbingHashTable lpht(table_size, step);

    for (const string &word : words) {
        cout << "Word: " << word
            << ", Hash1: " << Hash1(word, table_size) << ", Hash2: " << Hash2(word, table_size) << endl;
    }
cout<<"======================================"<<endl;
    for (const string &word : words) {
        unsigned int id = lpht.insert(word);
        if (id)
            cout << "Inserted: " << word << " with value " << id << endl;
        else
            cout << "Duplicate: " << word << endl;
    }

    cout << "Search datastr: " << lpht.search("datastr") << endl;
    cout << "Delete datastr: " << (lpht.remove("datastr") ? "Deleted" : "Not found") << endl;
    cout << "Search datastr: " << lpht.search("datastr") << endl;
cout<<"======================================"<<endl;
    DoubleHashingHashTable dhht(table_size);
    for (const string &word : words) {
        unsigned int id = dhht.insert(word);
        if (id)
            cout << "Inserted: " << word << " with value " << id << endl;
        else
            cout << "Duplicate: " << word << endl;
    }

    cout << "Search hashing: " << dhht.search("hashing") << endl;
    cout << "Delete hashing: " << (dhht.remove("hashing") ? "Deleted" : "Not found") << endl;
    cout << "Search hashing: " << dhht.search("hashing") << endl;

    return 0;
}
