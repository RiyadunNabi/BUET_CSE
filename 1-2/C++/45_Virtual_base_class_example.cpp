#include <iostream>
using namespace std;

// 
class Student
{
    protected:
    int roll;

    public:
    void set_roll(int a)
    {
        roll=a;
    }
    void printRoll()
    {
        cout<<"The Roll no is: "<<roll<<endl;
    }
};

class Test : public virtual Student //virtual public Student
{
   
    protected:
    float maths,physics;

    public:
    void set_Marks(float m,float p)
    {
        maths=m;
        physics=p;
    }
    void printMarks()
    {
        cout<<"Your result is: Maths="<<maths<<" Physics="<<physics<<endl;
    }
};
class Sports:public virtual Student
{
    protected:
    float score;

    public:
    void set_score(float s)
    {
        score=s;
    }
    void printScore()
    {
        cout<<"Your sports score is: "<<score<<endl;
    }
};

class Result : public Test, public Sports
{
    private:
    float total;

    public:
    void displayResult()
    {
        total=maths+physics+score;
        printRoll();
        printMarks();
        printScore();
        cout<<"Your final Result is: "<<total<<endl;

    }
};


int main()
{
    Result riyaad;
    riyaad.set_roll(2205076);
    riyaad.set_Marks(87,92);
    riyaad.set_score(50);
    riyaad.displayResult();


    return 0;
}