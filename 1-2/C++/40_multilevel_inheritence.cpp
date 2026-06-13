#include <iostream>
using namespace std;
//______________________________________________________________________________________________________________________
class Student
{
    protected:
    int roll_number;

    public:
    void set_roll_number(int);
    void get_roll_number();
};
void Student::set_roll_number(int r)
{
    roll_number=r;
}
void Student::get_roll_number()
{
    cout << "The roll number is " << roll_number << endl;
}
//____________________________________________________________________________________________________________________

class Exam : public Student
{
    protected:
    float maths,physics;

    public:
    void set_marks(float, float);
    void get_marks(void);
};
void Exam::set_marks(float m,float p)
{
    maths=m;
    physics=p;
}
void Exam::get_marks()
{
    cout << "The marks obtained in maths are: " << maths << endl;
    cout << "The marks obtained in physics are: " << physics << endl;
}
//_______________________________________________________________________________________________________________

class Result : public Exam
{
    float percentage;

    public:
    void display_result()
    {
        get_roll_number();
        get_marks();
        cout << "Your result is " << (maths + physics) / 2 << "%" << endl;
    }
};
//___________________________________________________________________________________________________________________
int main()
{
    Result harry;
    harry.set_roll_number(420);
    harry.set_marks(94.0, 90.0);
    harry.display_result();

    //Test
    cout<<"\n\nTest\n";
    harry.get_marks();
    harry.get_roll_number();


    return 0;
}