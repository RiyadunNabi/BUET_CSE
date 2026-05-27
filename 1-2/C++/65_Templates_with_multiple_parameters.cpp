#include <iostream>
using namespace std;

template <class T1, class T2>
class MyClass
{
    public:
    T1 data1;
    T2 data2;

    MyClass(T1 a, T2 b)
    {
        data1=a;
        data2=b;
    }
    void display()
    {
        cout<<this->data1<<" "<<this->data2<<endl;
    }
};

int main()
{
    MyClass<int, char> obj1(3,'r');
    obj1.display();

    MyClass<char, int> obj2('3',99);
    obj2.display();

    MyClass<float, char> obj3(4.5,'y');
    obj3.display();

    return 0;
}