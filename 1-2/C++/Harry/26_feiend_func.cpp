#include <iostream>
using namespace std;

/*******FRIEND FUNCTION**********//*
Properties of friend functions
1. Not in the scope of class
2. since it is not in the scope of the class, it cannot be called from the object of that class. c1.sumComplex() == Invalid
3. Can be invoked without the help of any object
4. Usually contans the objects as arguments
5. Can be declared inside public or private section of the class
6. It cannot access the members directly by their names and need object_name.member_name to access any member.
   like cout<<a; not valid;

*//******************/


class Complex
{
    int a;
    int b;

public:
    void setNumber(int x, int y)
    {
        a = x;
        b = y;
    }

    void printNumber()
    {
        cout << "Complex Number is: " << a << "+" << b << "i" << endl;
    }

    friend Complex sumComplex(Complex z1,Complex z2); //it can access private data of this class
    //non member - sumComplex can do anything with the class's private part(members)
};

Complex sumComplex(Complex z1,Complex z2){
    Complex z3;
    z3.setNumber(z1.a+z2.a, z1.b+z2.b); //its accessing private data of complex class

    return z3;
}

int main()
{
    Complex z1,z2,sum;
    z1.setNumber(2,3);
    z1.printNumber();

    z2.setNumber(4,7);
    z2.printNumber();

    sum=sumComplex(z1,z2);
    sum.printNumber();

    return 0;
}