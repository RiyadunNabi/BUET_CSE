#include <iostream>
using namespace std;

class BaseClass
{
public:
    int var_base;
    void display()
    {
        cout << "1. Dispalying Base class variable var_base " << var_base << endl;
    }
};
class DerivedClass : public BaseClass
{
public:
    int var_derived;
    void display()
    {
        cout << "2. Dispalying Base class variable var_base " << var_base << endl;
        cout << "2. Dispalying Derived class variable derived_base " << var_derived << endl;
    }
};

int main()
{
    cout << endl<<"Demonstration of base_class_pointer" << endl;
    BaseClass obj_base;
    DerivedClass obj_derived;

    BaseClass *base_class_pointer;
    base_class_pointer = &obj_derived; // Pointing base class pointer to derived class

    base_class_pointer->var_base = 22;
    base_class_pointer->display(); // base class function will execute

    // base_class_pointer->var_derived= 134; // Will throw an error

    cout << endl<<"Demonstration of derived_class_pointer" << endl;

    DerivedClass *derived_class_pointer;
    derived_class_pointer = &obj_derived;
    derived_class_pointer->var_base = 100;
    derived_class_pointer->var_derived = 200;
    derived_class_pointer->display(); // derived class function will execute
    return 0;
}