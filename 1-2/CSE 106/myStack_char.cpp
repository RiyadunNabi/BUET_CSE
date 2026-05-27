#include <iostream>
#include <string>
using namespace std;

class myStack_char
{
    string str;
    int topIndex;

    public:
    myStack_char()
    {
        topIndex=-1;
    }
    void push(char c)
    {
        if(topIndex == str.size()-1)
        {
            str.push_back(c);
            topIndex++;
            return;
        }
        str[++topIndex]=c;
    }
    void pop()
    {
        if(topIndex==-1)
        {
            cout<<"Stack is empty"<<endl;
            return;
        }
        topIndex--;
    }
    char top()
    {
        if(topIndex==-1)
        {
            cout<<"Stack is empty"<<endl;
            return -1;
        }
        return str.at(topIndex);

    }

    int size()
    {
        return topIndex+1;
    }

    bool isEmpty()
    {
        return topIndex==-1;
    }

};
int main()
{
    myStack_char s;
    for (int i = 0; i < 5; i++)
    {
        char c;
        cin>>c;
        s.push(c);
    }
    while (!s.isEmpty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }
    cout<<endl;
    
}