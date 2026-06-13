#include <iostream>
using namespace std;

template <class T1=int, class T2=char, class T3=float>
class MyClass
{
    public:
    T1 data1;
    T2 data2;
    T3 data3;

    MyClass(T1 a, T2 b, T3 c)
    {
        data1=a;
        data2=b;
        data3=c;
    }
    void display()
    {
        cout<<this->data1<<" "<<this->data2<<" "<<this->data3<<endl;
    }
};

int main()
{
    MyClass<int, float, char> obj1(3,4.9,'c');
    obj1.display();

    MyClass<> obj2(120 ,'p',99.33);  //default template parameter
    obj2.display();

    MyClass<float, int ,char> obj3(4.5,6,'y');
    obj3.display();

    return 0;
}