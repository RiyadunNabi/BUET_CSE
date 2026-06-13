#include <iostream>
using namespace std;

class Stack
{
private:
    int *array;
    // write your code here. Add additional private variables if necessary
    int capacity;
    int topIndex;

public:
    // Constructor
    Stack()
    {
        array = new int[1];
        // write your code here. Initialize additional private variables if necessary
        topIndex = 0;
        capacity = 1;
    }
    Stack(int initialCapacity)
    {
        array = new int[initialCapacity]; // Allocate initial memory
        // write your code here. Initialize additional private variables if necessary
        topIndex = 0;
        capacity = initialCapacity;
    }

    // Destructor
    ~Stack()
    {
        delete[] array; // Free dynamically allocated memory
    }

    // Helper function to resize the array when full
    void resize(int newCapacity)
    {
        int *newArray = new int[newCapacity]; // Allocate new array

        // write your code here. Copy the elements from the old array to the new array
        for (int i = 0; i < topIndex; i++)
        {
            newArray[i] = array[i];
        }
        delete[] array; // Free old memory

        // write your code here. Update the capacity and array pointers
        array = newArray;
        capacity = newCapacity;
    }

    // Push an element onto the stack
    void push(int x)
    {
        // write your code here. Check if the array is full and resize if necessary.
        if (topIndex == capacity)
        {
            resize(capacity * 2);
        }
        // push the element onto the stack
        array[topIndex++] = x;
    }

    // Remove and return the top element
    int pop()
    {
        // write your code here. Check if the stack is empty and return -1 if it is.
        if (topIndex == 0)
        {
            return -1;
        }
        // pop the top element and return it
        int value = array[--topIndex];
        // resize the array if necessary
        // if (topIndex>0 && (topIndex / (float)capacity <= 0.25))
        // {
        //     resize(capacity / 2);
        // }
        if (topIndex > 0 && topIndex <= capacity / 4)
        {
            resize(capacity / 2);
        }

        return value;
    }

    // Return the top element without removing it
    int top()
    {
        // write your code here. Check if the stack is empty and return -1 if it is.
        if (topIndex == 0)
        {
            return -1;
        }
        // return the top element
        return array[topIndex - 1];
    }

    // Return the number of elements in the stack
    int length()
    {
        // write your code here. Return the number of elements in the stack
        return topIndex;
    }

    // Check if the stack is empty
    bool isEmpty()
    {
        // write your code here. Return true if the stack is empty, false otherwise
        if (topIndex == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // Clear the stack
    void clear()
    {
        // write your code here. Clear the stack. resize the array to 1
        topIndex = 0;
        capacity = 1;
        // resize(1);
        int *newArray = new int[1];
        delete[] array;
        array = newArray;
    }
};
