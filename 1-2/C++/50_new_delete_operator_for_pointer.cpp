#include <iostream>
using namespace std;

int main()
{
    //----------------------------------------------------------------------------------------------------------------------------------------------------

    // Basic Example
    int a = 4;
    int *ptr = &a;
    cout << "The value of a is " << *(ptr) << endl
         << endl;

    //---------------------------------------------------------------------------------------------------------------------------------------------------

    float *p = new float(40.78);
    cout << "The value at address p is (before deallocating) = " << *(p) << endl;
    delete p;
    cout << "The value at address p is (after deallocating) = " << *(p) << endl;

    //----------------------------------------------------------------------------------------------------------------------------------------------------

    int *arr = new int[3];
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    cout << "\nThe values are: (before deallocating)" << endl;
    cout << "arr[0] = " << arr[0] << endl;
    cout << "*(arr+1) = " << *(arr + 1) << endl;
    cout << "arr[2] = " << arr[2] << endl;

    delete[] arr; // free the allocated

    cout << "\nThe values are: (after deallocating)" << endl;
    cout << "arr[0] = " << arr[0] << endl;
    cout << "*(arr+1) = " << *(arr + 1) << endl;
    cout << "arr[2] = " << arr[2] << endl;

    return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
/*from GEEKSFORGEEKS

int *p = NULL;      // Pointer initialized with NULL
p = new int;        // Then request memory for the variable

OR,

int *p = new int;   // Combine declaration of pointer and their assignment

*/
//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
//Their code
#include <iostream>
#include <memory>
using namespace std;

int main()
{

    int* ptr;       // pointer to store the address returned by the new
    ptr = new int;  // allocating memory for integer
    *ptr = 10;      // assigning value using dereference operator

    //printing value and address
    cout << "Address: " << ptr << endl;
    cout << "Value: " << *ptr;

    return 0;
}
*/
