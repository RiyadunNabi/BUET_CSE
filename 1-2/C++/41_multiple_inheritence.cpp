#include <iostream>
using namespace std;
/******************************************** */
class Base1
{
protected:
    int data1;

public:
    void set_data1(int a)
    {
        data1 = a;
    }
};
/****************************************** */
class Base2
{
protected:
    int data2;

public:
    void set_data2(int a)
    {
        data2 = a;
    }
};
/******************************************* */
class Base3
{
protected:
    int data3;

public:
    void set_data3(int a)
    {
        data3 = a;
    }
};
/******************************************** */
/*
Syntax of Multiple Inheritance
class DerivedC: visibility-mode base1, visibility-mode base2
{
     Class body of class "DerivedC"
};
*/
/******************************************** */
class Derived : public Base1, public Base2, public Base3
{
public:
    void show()
    {
        cout << "The value of Base1 is " << data1 << endl;
        cout << "The value of Base2 is " << data2 << endl;
        cout << "The value of Base3 is " << data3 << endl;
        cout << "The sum of these values is " << data1 + data2 + data3 << endl;
    }
};
int main()
{
    Derived riyaaaaad;
    riyaaaaad.set_data1(5);
    riyaaaaad.set_data2(10);
    riyaaaaad.set_data3(20);
    riyaaaaad.show();

    return 0;
}