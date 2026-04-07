#include <iostream>
using namespace std;

int main() {
    cout << "Hello, BUET CSE!" << endl;
    
    int a, b;
    cout << "Enter two numbers to add: ";
    if (cin >> a >> b) {
        cout << "The sum is: " << a + b << endl;
    }
    
    return 0;
}
