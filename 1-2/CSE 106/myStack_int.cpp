#include <iostream>
using namespace std;

class myStack
{
    int array[50];
    int topIndex;
    int maxSize;

    public:
    myStack()
    {
        topIndex=-1;
        maxSize=5;
    }
    void push(int x)
    {
        if(topIndex == maxSize-1)
        {
            cout<<"Stack is full"<<endl;
            return;
        }

        array[++topIndex]=x;
    }

    void pop()
    {
        if(topIndex==-1)
        {
            cout<<"STack is empty!"<<endl;
            return;
        }
        topIndex--;
    }

    int top()
    {
        if(topIndex==-1)
        {
            cout<<"Stack is empty"<<endl;
            return -1;
        }
        return array[topIndex];
    }

    bool empty()
    {
        return topIndex==-1;
    }

    int size()
    {
        return topIndex+1;
    }

    void printElements()
    {
        for(int i=0; i<=topIndex; i++)
        {
            cout<<array[i]<<" ";
        }
        cout<<endl;
    }
};

int main()
{
    myStack s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(5);
    s1.push(6);
    s1.printElements();

    cout<<s1.top()<<" "<<endl;;
    s1.pop();
    s1.printElements();

    cout<<s1.top()<<" "<<endl;
    s1.pop();
    s1.printElements();

    cout<<s1.top()<<" "<<endl;
    s1.pop();
    s1.printElements();


    cout<<endl;

    

    return 0;
}