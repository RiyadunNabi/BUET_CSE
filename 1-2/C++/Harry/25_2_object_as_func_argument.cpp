#include <iostream>
using namespace std;

class Complex
{
    int a;
    int b;

public:
    void setData(int x, int y)
    {
        a = x;
        b = y;
    }

    void setDataBySum(Complex z1, Complex z2) // Passing Objects as Function Arguments
    {
        a = z1.a + z2.a;
        b = z1.b + z2.b;
    }

    void printNumber()
    {
        cout << "Complex Number is: " << a << "+" << b << "i" << endl;
    }
};

int main()
{
    Complex c1, c2, c3;

    c1.setData(1, 2);
    c1.printNumber();

    c2.setData(4, 3);
    c2.printNumber();

    c3.setDataBySum(c1, c2); // Passing Objects as Function Arguments
    c3.printNumber();

    return 0;
}