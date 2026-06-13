#include <iostream>
using namespace std;

class Number
{
    int a;

    public:
    //Number(){}  //see previous example and must watch video from 4:00
/*or*/
    Number(){a=0;}
    Number(int n)  //or if it is default, then no need blank constructor
    {              // Number(int n=0)
        a=n;
    }
    /****************************************************************/
    //Copy constructor 
    //When no copy constructor is found/defined in code, then compiler supplies its own copy constructor 
    Number(Number &obj)
    {
        a=obj.a;
        cout<<"Copy Constructor Invoked!!!"<<endl;
    }
    /***************************************************************/
    void display()
    {
        cout<<"The number is: "<<a<<endl;
    }
};

int main()
{
    Number x,y(34);
    x.display();
    y.display();

    //copy constructor
    Number z1(y); //copy constructor invoked/called
    z1.display();


    //
    Number z3 = y; //copy constructor is invoked as it's constructor is called during is creation time
    z3.display();


    //
    Number z2;  //z2 is already created.
    z2=y;  //copy constructor will not be called as z2 is already created.
    z2.display();

    


    return 0;
}