#include <iostream>
using namespace std;


class Y;
class X{
    int data;
    public:
    void setValue(int value){
        data=value;
    }
    friend void add(X,Y);   //Needs forward declaration
};

class Y{
    int num;
    public:
    void setValue(int value){
        num = value;
    }
    friend void add(X,Y);
};

void add(X o1, Y o2){
    cout<<"Sum is: "<<o1.data+o2.num<<endl;
}

int main()
{
    X Ox;
    Ox.setValue(5);

    Y Oy;
    Oy.setValue(3);

    add(Ox,Oy);

    return 0;
}