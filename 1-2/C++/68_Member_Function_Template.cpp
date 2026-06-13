#include <iostream>
using namespace std;

template <class T>
class Harry
{
public:
    T data;
    Harry(T a)
    {
        data = a;
    }
    void display();
    // {
    //     cout << data;
    // }
};
template <class T>
void Harry<T> :: display(){
    cout<<data<<endl;
}


int main()
{
    Harry<float> h1(7.8);
    //cout << h1.data << endl;
    h1.display();

    Harry<int> h2(7);
    h2.display();

    Harry<char> h3('a');
    h3.display();

    return 0;
}