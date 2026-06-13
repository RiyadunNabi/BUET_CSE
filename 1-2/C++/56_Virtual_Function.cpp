/*
#myOpinion
Base Class, Derived Class sobgular moddhei jodi same naam er function thake, tahle,
jokhon Base Class pointer(jeta kono object ke point korbe), 
sei pointer diye object er vetorer (same naam er) function execute korte chaileo tokhon Base er function execute hoy.

aar ta prevent korar jonno tokhon base er function er age Virtual lagaye VIRTUAL FUNCTION banate hoy.
tahole, Derived class er function e execute hobe.
aar jodi Derived class er moddhe oi naam er function naoo thake tahole virtual kora holeo Base er function e execute hobe...........
*/

#include <iostream>
using namespace std;

class BaseClass
{
public:
    int var_base=1;
    virtual void display()         //IMPORTANTTTTTTTTTTTTTTTT
    {
        cout << "1. Dispalying Base class variable var_base = " << var_base << endl;
    }
};
class DerivedClass : public BaseClass
{
public:
    int var_derived=2;
    void display()
    {
        cout << "2. Dispalying Base class variable var_base = " << var_base << endl;
        cout << "2. Dispalying Derived class variable derived_base = " << var_derived << endl;
    }
};

int main()
{
    BaseClass obj_base;
    DerivedClass obj_derived;

    BaseClass *base_class_pointer;
    base_class_pointer = &obj_derived; // Pointing base class pointer to derived class

    base_class_pointer->display(); // base class function will execute if display function of base is not virtual
                                   // if base display function is virtual, then objects display function will be executed. 
                    


    return 0;
}