#pragma once
#include "2205076_SymbolInfo.hpp"
#include "2205076_Hash.hpp"

#include <string>
#include <iostream>

using namespace std;

class ScopeTable {
private:
    int num_buckets;           // Total number of buckets in the hash table [cite: 258]
    SymbolInfo** buckets;      // Array of SymbolInfo pointers for separate chaining [cite: 235]
    
    ScopeTable* parent_scope;  // Pointer to the parent scope table [cite: 259]
    int scope_id;              // Unique identifier for this scope [cite: 260]

    ostream& out; // The stream where all prints will go

public:
    ScopeTable(int n, int id, ScopeTable* parent, ostream& out_stream = cout) 
        : out(out_stream) 
    {
        this->num_buckets = n;
        this->scope_id = id;
        this->parent_scope = parent;
        
        this->buckets = new SymbolInfo*[num_buckets];
        for (int i = 0; i < num_buckets; i++) {
            this->buckets[i] = nullptr;
        }
    }

    // Destructor: Safely deallocate all memory [cite: 272, 327]
    ~ScopeTable() {
        for (int i = 0; i < num_buckets; i++) {
            SymbolInfo* curr = buckets[i];
            while (curr != nullptr) {
                SymbolInfo* temp = curr;
                curr = curr->getNext();
                delete temp; 
            }
        }
        delete[] buckets;
    }

    // Insert: Hash the name, go to bucket, insert if it doesn't already exist [cite: 261-263]
    bool Insert(string name, string type) {
        unsigned int index = SDBMHash(name, num_buckets);
        SymbolInfo* curr = buckets[index];
        int pos_in_chain = 1;

        while (curr != nullptr) {
            if (curr->getName() == name) {
                out << "\t'" << name << "' already exists in the current ScopeTable\n";
                return false; 
            }
            curr = curr->getNext();
            pos_in_chain++;
        }

        SymbolInfo* newNode = new SymbolInfo(name, type);
        
        if (buckets[index] == nullptr) {
            buckets[index] = newNode;
            pos_in_chain = 1; 
        } else {
            curr = buckets[index];
            while (curr->getNext() != nullptr) {
                curr = curr->getNext();
            }
            curr->setNext(newNode);
        }
        
        out << "\tInserted in ScopeTable# " << scope_id << " at position " << (index + 1) << ", " << pos_in_chain << "\n";
        return true;
    }

    // Lookup Method
    SymbolInfo* Lookup(string name, bool printResult = false) {
        unsigned int index = SDBMHash(name, num_buckets);
        SymbolInfo* curr = buckets[index];
        int pos_in_chain = 1;

        while (curr != nullptr) {
            if (curr->getName() == name) {
                if (printResult) {
                    out << "\t'" << name << "' found in ScopeTable# " << scope_id << " at position " << (index + 1) << ", " << pos_in_chain << "\n";
                }
                return curr;
            }
            curr = curr->getNext();
            pos_in_chain++;
        }
        return nullptr;
    }

    // Delete Method
    bool Delete(string name) {
        unsigned int index = SDBMHash(name, num_buckets);
        SymbolInfo* curr = buckets[index];
        SymbolInfo* prev = nullptr;
        int pos_in_chain = 1;

        while (curr != nullptr) {
            if (curr->getName() == name) {
                if (prev == nullptr) {
                    buckets[index] = curr->getNext();
                } else {
                    prev->setNext(curr->getNext());
                }
                
                delete curr;
                out << "\tDeleted '" << name << "' from ScopeTable# " << scope_id << " at position " << (index + 1) << ", " << pos_in_chain << "\n";
                return true;
            }
            prev = curr;
            curr = curr->getNext();
            pos_in_chain++;
        }
        
        out << "\tNot found in the current ScopeTable\n";
        return false;
    }

    // Print Method
    void Print() {
        out << "\tScopeTable# " << scope_id << "\n";
        for (int i = 0; i < num_buckets; i++) {
            out << "\t" << (i + 1) << "--> ";
            SymbolInfo* curr = buckets[i];
            
            while (curr != nullptr) {
                out << "<" << curr->getName() << "," << curr->getType() << "> ";
                curr = curr->getNext();
            }
            out << "\n";
        }
    }

    // Getters
    ScopeTable* getParentScope() { return parent_scope; }
    int getScopeId() { return scope_id; }
};