#include <iostream>
using namespace std;
//Forward declaration
class complex;

class calculator{
    public:
    int add(int a, int b){
        return (a+b);
    }

    int sumRealComplex(complex, complex);
    int sumComComplex(complex, complex);
};

class complex{
    int a,b;

    //Individually declearing functions as friends
    /*friend int calculator::sumRealComplex(complex,complex);
    friend int calculator::sumComComplex(complex,complex);*/

    //Aliter: if such functions are so many then it is difficult to friend them one by one
    //So, friend the whole class
    friend class calculator; //or, friend calculator;

    public:
    void setData(int x, int y){
        a=x; 
        b=y;
    }

    void printNumber(){
        cout << "Complex Number is: " << a << "+" << b << "i" << endl;
    }
};


int calculator::sumRealComplex(complex c1,complex c2){
    return c1.a+c2.a;
}
int calculator::sumComComplex(complex c1, complex c2){
    return c1.b+c2.b;
}


int main()
{
    complex z1,z2;
    z1.setData(2,3);
    z2.setData(9,3);

    calculator calc;
    int realResult=calc.sumRealComplex(z1,z2);
    cout<<"Sum of real is "<<realResult<<endl;

    int ComResult=calc.sumComComplex(z1,z2);
    cout<<"Sum of real is "<<ComResult<<endl;


    return 0;
}