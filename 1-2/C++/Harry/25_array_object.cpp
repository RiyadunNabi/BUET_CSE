#include <iostream>
using namespace std;

class Employee{
    int id;
    int salary;
    public:
    void setId(void){
        cout<<"Enter ID: ";
        cin>>id;
    }

    void getId(void){
        cout<<"The ID of this employee is "<<id<<endl;
    }
};

int main()
{
    //WHEN EMPLOYEE NO IS LESS
    // Employee riyad, safwan, fardin, azizul;
    // riyad.setId();
    // riyad.getId();

    //IF EMPLOYEE NO IS BIG
    Employee fb[4];
    for(int i=0; i<4; i++)
    {
        fb[i].setId();
        fb[i].getId();
    }

    return 0;
}