#include <iostream>
using namespace std;

template <class T> 
class Vector
{
    public:
    T* arr;
    int size;
    Vector(int m)
    {
        size=m;
        arr = new T[size];
    }

    T dotProduct(Vector &v)  //Pass by Reference   //if Vector v; then it will also shows correct result;
    {
        T d=0;
        for(int i=0; i<size; i++)
        {
            d+=this->arr[i] * v.arr[i];
        }
        return d;
    }
};

int main()
{
    Vector <int>v1(3); //Vector 1
    v1.arr[0] = 4;
    v1.arr[1] = 3;
    v1.arr[2] = 1;

    Vector <int>v2(3); //Vector 2
    v2.arr[0]=1;
    v2.arr[1]=0;
    v2.arr[2]=1;
    int a1 = v1.dotProduct(v2);
    cout<<"int dot product : "<<a1<<endl;
//------------------------------------------------------------------------------------------------------------------------------------------------------------
    Vector <float>v3(3); //Vector 3
    v3.arr[0] = 2.1;
    v3.arr[1] = 10;
    v3.arr[2] = 1;

    Vector <float>v4(3); //Vector 4
    v4.arr[0]=10;
    v4.arr[1]=0.2;
    v4.arr[2]=0.5;
    float a2 = v3.dotProduct(v4);
    cout<<"float dot product : "<<a2<<endl;


    return 0;
}