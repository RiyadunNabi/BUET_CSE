#pragma once
#include "2205076_ScopeTable.hpp"
#include <iostream>
#include <string>

using namespace std;

class SymbolTable {
private:
    ScopeTable* current_scope; 
    int num_buckets;           
    int scope_count;           
    ostream& out;              

public:
    // Constructor
    SymbolTable(int n, ostream& out_stream = cout) : num_buckets(n), out(out_stream) {
        current_scope = nullptr;
        scope_count = 0;
        
        // Immediately enter the global scope upon creation of the symbol table
        EnterScope();
    }

    // Destructor: Safely unwinds the stack and deletes everything
    ~SymbolTable() {
        while (current_scope != nullptr) {
            ScopeTable* temp = current_scope;
            current_scope = current_scope->getParentScope();
            out << "\tScopeTable# " << temp->getScopeId() << " removed\n"; // Matches 'Q' command output 
            delete temp;
        }
    }

    // Enter Scope: Push a new table onto the stack
    void EnterScope() {
        scope_count++;
        ScopeTable* newScope = new ScopeTable(num_buckets, scope_count, current_scope, out);
        current_scope = newScope;
        out << "\tScopeTable# " << scope_count << " created\n";
    }

    // Exit Scope: Pop the top table off the stack
    void ExitScope() {
        if (current_scope == nullptr) return;
        
        // Spec strictly says: "Note that you cannot exit the root scope table." [cite: 304]
        if (current_scope->getScopeId() == 1) {
            out << "\tScopeTable# 1 cannot be removed\n";
            return;
        }
        
        ScopeTable* temp = current_scope;
        current_scope = current_scope->getParentScope();
        out << "\tScopeTable# " << temp->getScopeId() << " removed\n";
        delete temp;
    }

    // Insert into current scope
    bool Insert(string name, string type) {
        if (current_scope != nullptr) {
            return current_scope->Insert(name, type);
        }
        return false;
    }

    // Remove from current scope
    bool Remove(string name) {
        if (current_scope != nullptr) {
            return current_scope->Delete(name);
        }
        return false;
    }

    // Lookup across all scopes [cite: 283-285]
    SymbolInfo* Lookup(string name) {
        ScopeTable* temp = current_scope;
        
        while (temp != nullptr) {
            // Passing 'true' tells ScopeTable to print the success message if found
            SymbolInfo* result = temp->Lookup(name, true); 
            
            if (result != nullptr) {
                return result; // Found it, stop searching
            }
            // Not found in this scope, move down the stack to the parent
            temp = temp->getParentScope(); 
        }
        
        // Checked every scope and found nothing
        out << "\t'" << name << "' not found in any of the ScopeTables\n";
        return nullptr;
    }

    // Print only the current scope
    void PrintCurrentScopeTable() {
        if (current_scope != nullptr) {
            current_scope->Print(); 
        }
    }

    // Print all active scopes
    void PrintAllScopeTable() {
        ScopeTable* temp = current_scope;
        while (temp != nullptr) {
            temp->Print();
            temp = temp->getParentScope();
        }
    }
};