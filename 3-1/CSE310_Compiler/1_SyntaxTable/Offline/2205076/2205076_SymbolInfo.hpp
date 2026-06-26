#pragma once
#include <string>
#include <iostream>

using namespace std;

class SymbolInfo {
private:
    string name;
    string type;
    SymbolInfo* next; // Pointer for separate chaining

public:
    SymbolInfo(string name, string type){
        this->name = name;
        this->type = type;
        this->next = nullptr;
    }

    // TODO: Write Getters
    string getName() {
        return name;
    }
    string getType() {
        return type;
    }
    SymbolInfo* getNext() {
        return next;
    }

    void setName(string name) {
        this->name = name;
    }
    void setType(string type) {
        this->type = type;
    }
    void setNext(SymbolInfo* next) {
        this->next = next;
    }



	void showSymbolInfo()
	{
		cout<<endl<<"Symbol Info:"<<endl;
		cout<<"Name = "<<name<<endl;
		cout<<"Type = "<<type<<endl;
		cout<<endl;
	}
};