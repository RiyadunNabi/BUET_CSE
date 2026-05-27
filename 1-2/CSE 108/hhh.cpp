#include <iostream>
using namespace std;

class Complex
{
private:
    float real;
    float imag;

public:
    // Constructor to initialize complex number
    Complex(float r = 0, float i = 0) : real(r), imag(i) {}

    // Overloading the '+' operator as a member function
    Complex operator+(const Complex &obj)
    {
        Complex temp;
        temp.real = real + obj.real; // Add real parts
        temp.imag = imag + obj.imag; // Add imaginary parts
        return temp;
    }

    // A function to display the complex number
    void display()
    {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main()
{
    
}
