#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Rectangle
{
    float length,width;
    char* colour;
    public:
    Rectangle(int a,int b, const char* c)
    {
        length=a;
        width=b;
        colour = new char[strlen(c)+1];
        strcpy(colour,c);
    }
    Rectangle()
    {
        length=0;
        width=0;
        colour = new char[strlen("undefined")+1];
        strcpy(colour,"undefined");
    }
    ~Rectangle()
    {
        delete[] colour;
    }
    float getPerimeter()
    {
        return 2*(length+width);
    }
    float getArea()
    {
        return length*width;
    }
    const char* getColor()
    {
        return colour;
    }
    void setColor(const char* c)
    {
        delete[] colour;
        colour = new char[strlen(c)+1];
        strcpy(colour,c);
    }
    float getLength()
    {
        return length;
    }
    float getWidth()
    {
        return width;
    }
};

class Triangle
{
    float a,b,c;
    char* colour;
    public:
    Triangle(float x,float y, float z, const char* c)
    {
        a=x;
        b=y;
        this->c=z;
        colour = new char[strlen(c)+1];
        strcpy(colour,c);
    }
    Triangle()
    {
        a=0;
        b=0;
        this->c=0;
        colour = new char[strlen("undefined")+1];
        strcpy(colour,"undefined");
    }
    ~Triangle()
    {
        delete[] colour;
    }
    float getPerimeter()
    {
        return (a+b+c);
    }
    const char* getColor()
    {
        return colour;
    }
    float getArea()
    {
        float s=(a+b+c)/2;
        return sqrt(s*(s-a)*(s-b)*(s-c));

    }
    void setColor(const char* c)
    {
        delete[] colour;
        colour = new char[strlen(c)+1];
        strcpy(colour,c);
    }

    float geta()
    {
        return a;
    }
    float getb()
    {
        return b;
    }
    float getc()
    {
        return c;
    }  
};

class Circle
{
    float radius;
    char* colour;
    public:
    Circle(float r, const char *c)
    {
        radius=r;
        colour=new char[strlen(c)+1];
        strcpy(colour,c);
    }
    Circle()
    {
        radius=0;
        colour = new char[strlen("undefined")+1];
        strcpy(colour,"undefined");
    }
    ~Circle()
    {
        delete[] colour;
    }
    float getPerimeter()
    {
        return 2*3.14*radius;
    }
    float getArea()
    {
        return 3.14*radius*radius;
    }
    const char* getColor()
    {
        return colour;
    }
    void setColor(const char* c)
    {
        delete[] colour;
        colour = new char[strlen(c)+1];
        strcpy(colour,c);
    }
    float getRadius()
    {
        return radius;
    }
};

class ShapeCollection
{
    Rectangle rctngl[100];
    Triangle trngl[100];
    Circle crcl[100];
    int count_r=0,count_t=0,count_c=0;

    public:
    void addRectangle(Rectangle &r)
    {
        rctngl[count_r++]=r;
    }
    void addTriangle(Triangle &t)
    {
        trngl[count_t++]=t;
    }
    void addCircle(Circle &c)
    {
        crcl[count_c++]=c;
    }
    int getRectCount()
    {
        return count_r;
    }
    int getTriCount()
    {
        return count_t;
    }
    int getCircCount()
    {
        return count_c;
    }
    void printRectangles()
    {
        for (int i = 0; i < count_r; i++)
        {
            cout<<"Rectangle "<<i<<": length: "<<rctngl[i].getLength()<<" width: "<<rctngl[i].getWidth()<<endl;
        } 
    }
    void printTriangles()
    {
        for (int i = 0; i < count_t; i++)
        {
            cout<<"Triangle "<<i<<": a: "<<trngl[i].geta()<<" b: "<<trngl[i].getb()<<" c: "<<trngl[i].getc()<<endl;
        } 
    }
    void printCircles()
    {
        for (int i = 0; i < count_c; i++)
        {
            cout<<"Circle "<<i<<": radious: "<<crcl[i].getRadius()<<endl;
        } 
    }

};






int main() {
    // Create rectangle with length, width, color
    Rectangle r1(10, 20, "Red");
    // The Color is stored using malloc, which will be freed during destruction
    cout << "Rectangle Perimeter: " << r1.getPerimeter() << endl;
    cout << "Rectangle Area: " << r1.getArea() << endl;
    cout << "Rectangle Color: " << r1.getColor() << endl;
    // When changing the color, you need to free the memory of the old color
    // and allocate new memory for the new color
    r1.setColor("Yellow");
    cout << "Rectangle Color: " << r1.getColor() << endl;
    cout << "--------------------------------------" << endl;



    // Create triangle with a, b, c, color. (a, b, c are lengths of the sides)
    Triangle t1(3, 4, 5, "Blue");
    cout << "Triangle Perimeter: " << t1.getPerimeter() << endl;
    cout << "Triangle Color: " << t1.getColor() << endl;
    cout << "Triangle Area: " << t1.getArea() << endl;
    t1.setColor("Orange");
    cout << "Triangle Color: " << t1.getColor() << endl;
    cout << "--------------------------------------" << endl;
 
    // Create circle with radius, color
    Circle c1(7, "Green");
    cout << "Circle Perimeter: " << c1.getPerimeter() << endl;
    cout << "Circle Area: " << c1.getArea() << endl;
    cout << "Circle Color: " << c1.getColor() << endl;
    c1.setColor("Purple");
    cout << "Circle Color: " << c1.getColor() << endl;
    cout << "--------------------------------------" << endl;
 
    /*
    When constructing the ShapeCollection class, you will create static arrays for 100 
    rectangles, triangles and circles. You don’t have to dynamically allocate memory for this.
    */ 
    ShapeCollection shapes;
    /* IMPORTANT: You need to pass the objects by reference to the add functions
    If you pass by value, the copy constructor will be called and the dynamically
    allocated memory will be copied, leading to double free errors when things go 
    out of scope. Once passed by reference, do not directly store the reference in 
    the array. Instead, copy the data from the reference to the array element.
    We will see better ways to handle this in the upcoming sessions.
    */ 
    shapes.addRectangle(r1);
    shapes.addTriangle(t1);
    shapes.addCircle(c1);
 
    Rectangle r2(15, 25, "Black");
    shapes.addRectangle(r2);
    Triangle t2(5, 12, 13, "White");
    shapes.addTriangle(t2);
 
    cout << "Number of Rectangles: " << shapes.getRectCount() << endl;
    cout << "Number of Triangles: " << shapes.getTriCount() << endl;
    cout << "Number of Circles: " << shapes.getCircCount() << endl;
    cout << "--------------------------------------" << endl;
 
    shapes.printRectangles();
    shapes.printTriangles();
    shapes.printCircles();
    
    return 0;
}