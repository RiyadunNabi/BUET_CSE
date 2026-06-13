#include <iostream>
#include <cmath>
using namespace std;

// Function to compute the square of a number using Divide and Conquer
int karatsubaSquare(int A) {
    if (A < 10) return A * A; // Base case: single digit squaring

    // Find number of digits
    int n = log10(A) + 1;
    int m = n / 2;
    
    // Split A into two halves
    int high = A / pow(10, m);
    int low = A % (int)pow(10, m);
    
    // Compute x^2, y^2, and (x + y)^2
    int highSq = karatsubaSquare(high);
    int lowSq = karatsubaSquare(low);
    int midSq = karatsubaSquare(high + low);
    
    // Compute 2xy = (x+y)^2 - x^2 - y^2
    int xy = (midSq - highSq - lowSq) / 2;
    
    // Compute final result : A² = x² * 10^(2m) + 2xy * 10^m + y²
    return highSq * pow(10, 2*m) + 2*xy*pow(10, m+1) + lowSq;
}

// Main function with embedded sample input
int main() {
    int A = 2678; // Sample input
    cout << "Square of " << A << " is: " << karatsubaSquare(A) << endl;
    return 0;
}
