#include <iostream>
using namespace std;
/*********first declaration, then definition outside of the class******/
class complex
{
    int a, b;

public:
    complex(int, int); // Constructor declaration

    void printNumber()
    {
        cout << "Your number is " << a << " + " << b << "i" << endl;
    }
};

complex::complex(int x, int y) // ----> This is a parameterized constructor as it accepts 2 parameters
{
    a = x;
    b = y;
    cout << "Hello world\n";
}
/********************************************************************** */
/*******declaration and definition both indside the class***************/
class Employee
{
    int ID, age;

public:
    Employee(int a, int b)
    {
        ID = a;
        age = b;
    }
    void displayData()
    {
        cout<<"ID = "<<ID<<" and age = "<<age<<endl;
    }
};
/******************************************************************** */
int main()
{
    // Not alloweded
    /* complex m;
    m.complex(4,2);
    m.printNumber();*/

    // implicit call
    complex n1(3, 4);
    n1.printNumber();

    // explicit call
    complex b = complex(5, 7);
    b.printNumber();
/******************************************************************** */
    Employee Riyad(2205076,22);
    Riyad.displayData();

    return 0;
}