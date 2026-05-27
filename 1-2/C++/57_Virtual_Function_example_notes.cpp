/*
Rules for VIRTUAL FUNCTIONs
1. They cannot be static
2. They are accessed by object pointers
3. VIRTUAL FUNCTIONs can be a friend of another class
4. A VIRTUAL FUNCTION in the base class might not be used.
5. If a VIRTUAL FUNCTION is defined in a base class, there is no necessity of redefining it in the derived class
*/
/*
#myOpinion
Base Class, Derived Class sobgular moddhei jodi same naam er function thake, tahle,
jokhon Base Class pointer(jeta kono object ke point korbe), 
sei pointer diye object er vetorer (same naam er) function execute korte chaileo tokhon Base er function execute hoy.

aar ta prevent korar jonno tokhon base er function er age Virtual lagaye VIRTUAL FUNCTION banate hoy.
tahole, Derived class er function e execute hobe.
aar jodi Derived class er moddhe oi naam er function naoo thake tahole virtual kora holeo Base er function e execute hobe...........
*/
#include <iostream>
#include <cstring>
using namespace std;

class CWH
{
protected:
    string title;
    float rating;

public:
    CWH(string s, float r)
    {
        title = s;
        rating = r;
    }
    virtual void display() {} // IT'S VIRTUAL. if not then it will be executed when we will call display function using pointer; TRY IT
};
class CWH_Video : public CWH
{
    float videolength;

public:
    CWH_Video(string s, float r, float vl) : CWH(s, r)
    {
        videolength = vl;
    }
    void display()
    {
        cout << "This is an amazing video with title: " << title << endl;
        cout << "Ratings: " << rating << " out of 5 stars" << endl;
        cout << "Length of this video is: " << videolength << " minutes" << endl;
    }
};
class CWH_Text : public CWH
{
    int words;

public:
    CWH_Text(string s, float r, int w) : CWH(s, r)
    {
        words = w;
    }
    void display()
    {
        cout << "This is an amazing text tutorial with title: " << title << endl;
        cout << "Ratings of this text tutorial: " << rating << " out of 5 stars" << endl;
        cout << "No of words in this text tutorial is: " << words << " words" << endl;
    }
};

int main()
{
    //----------------------------------------------------------------------------------------------------------------------------------------------------------------
    cout << endl;

    string title;
    float rating, vlength;
    int words;

    // for Video
    title = "VIRTUAL FUNCTIONs Example + Creation Rules";
    vlength = 28.5;
    rating = 4.5;
    CWH_Video video_obj(title, rating, vlength);
    // video_obj.display();

    // for text
    title = "Text tutorial";
    words = 120;
    rating = 4.1;
    CWH_Text text_obj(title, rating, words);
    // text_obj.display();
    //----------------------------------------------------------------------------------------------------------------------------------------------------------------
    cout << "USING POINTER" << endl
         << endl;

    // CWH tutorial[2]; //error because CWH has constructor with 2 arguments, we cannot make array of two objects without their constructor
    CWH *tutorial[2]; // array of CWH object pointers

    tutorial[0] = &video_obj;
    tutorial[1] = &text_obj;

    tutorial[0]->display();   // or,    (*tutorial[0]).display();    //not, *(tutorial[1]).display(); because * then dereferences whole tutorial[1].display()
    (*tutorial[1]).display(); // or      tutorial[1]->display();    //similarly

    cout << endl;
    return 0;
}
