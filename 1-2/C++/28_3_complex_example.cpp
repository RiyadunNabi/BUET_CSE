#include <iostream>
using namespace std;
class c2;
class c1
{
    int n1;
    friend void exchange(c1 &, c2 &);

public:
    void setData(int n)
    {
        n1 = n;
    }

    void display(){
        cout<<n1<<endl;
    }
};

class c2
{
    int n2;
    friend void exchange(c1 &, c2 &);

public:
    void setData(int n)
    {
        n2 = n;
    }
    void display(){
        cout<<n2<<endl;
    }
};

void exchange(c1 &obj1, c2 &obj2)
{
    int temp = obj1.n1;
    obj1.n1 = obj2.n2;
    obj2.n2 = temp;
}

int main()
{
    c1 obj1;
    obj1.setData(34);

    c2 obj2;
    obj2.setData(67);

    exchange(obj1,obj2);

    cout<<"After exhanging: n1 = ";
    obj1.display();

    cout<<"After exhanging: n2 = ";
    obj2.display();



    return 0;
}