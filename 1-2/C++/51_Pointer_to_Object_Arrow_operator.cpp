#include <iostream>
using namespace std;

class Complex
{
    int real, imaginary;

public:
    void set_Data(int a, int b)
    {
        real = a;
        imaginary = b;
    }

    void get_Data()
    {
        cout << "The real part is " << real << endl;
        cout << "The imaginary part is " << imaginary << endl
             << endl;
    }
};

int main()
{
    //--------------------------------------------------------------------------------------------------------------------------------------

    // Complex c1;
    // Complex* ptr = &c1;
    Complex *ptr = new Complex;

    //(*ptr).set_Data(1, 54); // is exactly same as
    ptr->set_Data(13, 5);

    //(*ptr).get_Data(); // is as good as
    ptr->get_Data();

    //--------------------------------------------------------------------------------------------------------------------------------------

    // Array of Objects
    Complex *ptr1 = new Complex[3];

    ptr1->set_Data(11, 11);
    ptr1->get_Data();

    (ptr1 + 1)->set_Data(22, 22);
    (ptr1 + 1)->get_Data();

    (ptr1 + 2)->set_Data(33, 33);
    (ptr1 + 2)->get_Data();
    //--------------------------------------------------------------------------------------------------------------------------------------

    return 0;
}