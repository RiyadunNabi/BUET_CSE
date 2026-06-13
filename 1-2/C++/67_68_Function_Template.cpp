#include <iostream>
using namespace std;
//-----------------------------------------------------------------------
//generally we would do
float funcAverage1(int a, int b)
{
    float avg = (a + b) / 2.0;
    return avg;
}
float funcAverage2(float a, int b)
{
    float avg = (a + b) / 2.0;
    return avg;
}
//-----------------------------------------------------------------------
//instead use template
template<class T1, class T2>
float funcAverage(T1 a, T2 b)
{
    float avg = (a + b) / 2.0;
    return avg;
}

//swapp func
template<class T>
void mySwap(T &a, T &b)
{
    T temp=a;
    a=b;
    b=temp;
}
//-----------------------------------------------------------------------
//overloading of a function template
void funcOverload(int a)   //Exact match takes the highest priority
{
    cout<<"I am first func() "<<a<<endl;
}
 
template<class T>
void funcOverload(T a)
{
    cout<<"I am templatised func() "<<a<<endl;
}


//just for example
template<class T>
void funcOverload_extra(T a)
{
    cout<<"I am templatised_extra func() "<<a<<endl;
}

//-----------------------------------------------------------------------
int main()
{
    //-----------------------------------------------------------------------
    cout<<"funcAverage1(3,4) = "<<funcAverage1(3,4)<<endl;
    cout<<"funcAverage2(3.5,4) = "<<funcAverage2(3.5,4)<<endl<<endl;
    //-----------------------------------------------------------------------
    cout<<"funcAverage(3,4) = "<<funcAverage(3,4)<<endl;
    cout<<"funcAverage(3,4.5) = "<<funcAverage(3,4.5)<<endl;
    cout<<"funcAverage(3.25,4.25) = "<<funcAverage2(3.5,4.5)<<endl<<endl;

    int a=5,b=7;
    swap(a,b);
    cout<<"swap(3,4) => a="<<a<<", b="<<b<<endl;

    float c=5.3,d=7.9;
    swap(c,d);
    cout<<"swap(5.3,7.9) => c="<<c<<", d="<<d<<endl<<endl;
    //-----------------------------------------------------------------------

    funcOverload(4); //Exact match takes the highest priority //so first func will execute
    funcOverload_extra(4); //now templatised func will be executed

    funcOverload(4.5);
    funcOverload('t');


    return 0;
}