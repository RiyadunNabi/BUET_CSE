#include <iostream>
using namespace std;

class point
{
    int x, y;

public:
    point(int a, int b=0)
    {
        x = a;
        y = b;
    }
    void displayPoint()
    {
        cout << "The point is (" << x << "," << y << ")" << endl;
    }
};
int main()
{
    point P(2);
    P.displayPoint();

    return 0;
}