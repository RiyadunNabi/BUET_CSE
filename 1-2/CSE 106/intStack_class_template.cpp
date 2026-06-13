#include <iostream>
#include <stack>

using namespace std;

int main()
{
    //-----------------------------------------------------------------------------------
    stack<int> s1;

    s1.push(5);
    s1.push(4);
    s1.push(3);
    s1.push(2);
    s1.push(1);
    s1.push(55);
    cout << "Size of stack: " << s1.size() << endl;

    for (int i = 5; i > 0; i--)
    {
        cout << "Top element at " << i << ": " << s1.top() << endl;
        s1.pop();
    }

    s1.pop();
    s1.pop();

    if (s1.empty())
    {
        cout << "Stack is empty" << endl;
    }
    else
    {
        cout << "Stack is not empty" << endl; // Output: Stack is not empty
    }

    //================================================================================

    stack<char> s2;

    s2.push('a');
    s2.push('b');
    s2.push('c');
    s2.push('d');
    s2.push('e');
    //s1.push(55);
    cout << "Size of stack: " << s2.size() << endl;

    for (int i = 5; i > 0; i--)
    {
        cout << "Top element at " << i << ": " << s2.top() << endl;
        s2.pop();
    }

    s2.pop();
    //s1.pop();

    if (s2.empty())
    {
        cout << "Stack is empty" << endl;
    }
    else
    {
        cout << "Stack is not empty" << endl; // Output: Stack is not empty
    }

    return 0;
}