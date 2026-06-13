#include <iostream>
using namespace std;

/*
//Characteristics of Constructors
1. it should be declared in the public section of the class
2. they are automatically invoked whenever the object is created
3. they cannot return values and Don't have return type
4. it can have default arguments
5. we cannot refer to their address
*/
/***********************first declaration, then definition outside of the class******************************************** */
class complex
{
    int a, b;

    // Creating a constructor
    // Constructor is a special member function with the same name as of the class.
    // It is used to initialize the objects of its class
    // **It is automatically invoked whenever an object is created**
public:
    complex(void); // Constructor declaration

    void printNumber()
    {
        cout << "Your number is " << a << " + " << b << "i" << endl;
    }
};

complex::complex(void) // ----> This is a default constructor as it accepts no parameters
{
    a = 4;
    b = 5;
    cout << "Hello world\n";
}
/******************************************************************** */
/***************declaration and definition both indside the class*********************** */
class complex_test
{
    int a, b;

    // Creating a constructor
    // Constructor is a special member function with the same name as of the class.
    // It is used to initialize the objects of its class
    // **It is automatically invoked whenever an object is created**
public:
    complex_test(void) // Constructor declaration
    {
        a = 9;
        b = 9;
        cout << "Test Hello world\n";
    }

    void printNumber()
    {
        cout << "Your number is " << a << " + " << b << "i" << endl;
    }
};
/*********************************************************************** */
int main()
{
    complex z1, z2, z3;
    z1.printNumber();
    z2.printNumber();
    z3.printNumber();

    complex_test y1,y2;
    y1.printNumber();
    y2.printNumber();

    return 0;
}
