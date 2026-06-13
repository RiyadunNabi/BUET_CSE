#include <iostream>

using namespace std;

class Rectangle
{
    int *width, *height;

public:
    Rectangle(int a, int b) // Constructor
    {
        cout<<"Constructor is called"<<endl;
        width = new int(a);
        height = new int(b);
    }
    Rectangle(const Rectangle &r) // Copy constructor
    {
        cout<<"Copy Constructor is called for "<<*(r.width)<<" "<<*(r.height)<<endl;
        width = new int;
        height = new int;
        *width = *r.width;
        *height = *r.height;
    }
    ~Rectangle() // Destructor
    {
        cout<<"Destructor is called"<<endl;
        delete width;
        delete height;
    }

    int area() // Method to calculate area
    {
        return (*width * *height);
    } 
};

// Function to return the larger rectangle based on area
Rectangle larger(Rectangle recta, Rectangle rectb)
{
    if (recta.area() > rectb.area())
        return recta;
    else
        return rectb;
}

int main()
{
    Rectangle recta(3, 4); // Create first rectangle
    Rectangle rectb(5, 6); // Create second rectangle

    Rectangle rectc = recta; // Calls copy constructor
    cout<<"rectc=recta\n";

    // Rectangle rect_larger(0, 0);      // Temporary object
    // rect_larger = larger(recta, rectb);  // Calls copy constructor and destructor

    Rectangle rect_larger1 = larger(recta, rectb);
    // Rectangle rect_larger2(larger(recta, rectb));

    cout << "recta area: " << recta.area() << endl;
    cout << "rectb area: " << rectb.area() << endl;
    cout << "rectc area: " << rectc.area() << endl;
    // cout << "rect_larger area: " << rect_larger.area() << endl;
    cout << "rect_larger1 area: " << rect_larger1.area() << endl;
    // cout << "rect_larger2 area: " << rect_larger2.area() << endl;

    return 0;
}