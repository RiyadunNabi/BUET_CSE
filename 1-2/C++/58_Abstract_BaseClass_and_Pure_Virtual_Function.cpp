/*
#Pure Virtual Functions:
Pure virtual function is a function that doesn’t perform any operation and 
the function is declared by assigning the value 0 to it. 
Pure virtual functions are declared in abstract classes.

#Abstract Base Class
Abstract base class is a class that has at least one pure virtual function in its body. 
The classes which are inheriting the base class must need to override the virtual function of the abstract class 
otherwise compiler will throw an error.


#myOpinion
Abstract Base class is like pure template class jekhane er moddhe toiri howa function gula nije kisu korbe na
kintu ei class theke jeshob objects banano hobe, segulote oi function gulo must thakbeiiii;
mane its like forcing the objects to make those functions.

ar eishob abstract base class er moddher (sob) function gula =0 likhte hoy, tahole tara PURE VIRTUAL FUNCTION hoy.
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
    virtual void display()=0; //PURE VIRTUAL FUNCTION
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
    title = "Virtual Functions Example + Creation Rules";
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
    (*tutorial[1]).display(); // or,     tutorial[1]->display();    //similarly

    cout << endl;
    return 0;
}
