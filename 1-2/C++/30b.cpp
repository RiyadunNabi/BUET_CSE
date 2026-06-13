#include <iostream>
#include <cmath>
using namespace std;

class Point{
    int x,y;
    friend float distance(Point,Point);
    public:
    Point(int a,int b)
    {
        x=a;
        y=b;
    }
    void displayPoint(){
        cout<<"The point is ("<<x<<","<<y<<")"<<endl;
    }

};
//Create a function (Hint: make it a feiend function)which takes 2 point
//objects and computes the distance between those 2 points

float distance(Point p, Point q)
{
    return sqrt((p.x - q.x)*(p.x - q.x) + (p.y-q.y)*(p.y-q.y));
}

int main()
{
    Point p(3,4);
    p.displayPoint();

    Point q(7,9);
    q.displayPoint();

    cout<<"Distance of p and q: "<<distance(p,q);

    return 0;
}