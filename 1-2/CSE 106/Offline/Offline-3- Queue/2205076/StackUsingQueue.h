#include <iostream>
#include "QueueLinkedList.h"
using namespace std;

class Stack
{
private:
    // write your code here. Add additional private variables if necessary
    Queue *que;

public:
    // Constructor
    Stack()
    {
        // write your code here. Initialize additional private variables if necessary
        que= new Queue;
    }
    Stack(int initialCapacity)
    {
        // write your code here. Initialize additional private variables if necessary
    }

    // Destructor
    ~Stack()
    {
        que->clear();
        delete que;
    }

    // Push an element onto the stack
    void push(int x)
    {
        // write your code here.
        // push the element onto the stack
        que->enqueue(x);
    }

    // Remove and return the top element
    int pop()
    {
        // write your code here. Check if the stack is empty and return -1 if it is.
        if (que->isEmpty())
        {
            return -1;
        }
        // pop the top element and return it
        Queue *tempQue=new Queue;
        while (que->length()>1)
        {
            tempQue->enqueue(que->dequeue());
        }
        int value = que->dequeue();
        que->clear();
        delete que;
        que=tempQue;
        return value;
    }

    // Return the top element without removing it
    int top()
    {
        // write your code here. Check if the stack is empty and return -1 if it is.
        if (que->isEmpty())
        {
            return -1;
        }
        // return the top element
        Queue *tempQue=new Queue;
        while (que->length()>1)
        {
            tempQue->enqueue(que->dequeue());
        }
        int value = que->dequeue();
        tempQue->enqueue(value);
        que->clear();
        delete que;
        que=tempQue;
        return value;
    }

    // Return the number of elements in the stack
    int length()
    {
        // write your code here. Return the number of elements in the stack
        return que->length();
    }

    // Check if the stack is empty
    bool isEmpty()
    {
        // write your code here. Return true if the stack is empty, false otherwise
        //que->isEmpty() ? true : false;
        return que->isEmpty();
    }

    // Clear the stack
    void clear()
    {
        // write your code here. Clear the stack.
        que->clear();
        //delete que;  //no, dont delete
    }
};
