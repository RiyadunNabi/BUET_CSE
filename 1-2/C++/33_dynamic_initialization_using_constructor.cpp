#include <iostream>
using namespace std;

class BankDeposite
{
    int principal, years;
    float interestRate, returnValue;

    public:
    BankDeposite(){} //it is needed for blank object; //see video 22:00
                    // if it not created , then the program will throw error for object having no p,y,r;
    BankDeposite(int p, int y, float r); //r is decimal
    BankDeposite(int p, int y, int r); //r is int
    void showFinalAmount();

};
BankDeposite::BankDeposite(int p, int y, float r)
{
    principal=p;
    years=y;
    interestRate=r;
    returnValue=p;
    for(int i=1; i<=y; i++)
    {
        returnValue=returnValue+returnValue*interestRate;
    }
    //return returnValue;
}
BankDeposite::BankDeposite(int p, int y, int r)
{
    principal=p;
    years=y;
    interestRate=(float)r/100;
    returnValue=p;
    for(int i=1; i<=y; i++)
    {
        returnValue=returnValue+returnValue*interestRate;
    }
    //return returnValue;
}
void BankDeposite::showFinalAmount()
{
    cout<<"principal="<<principal<<endl<<"years=" <<years<<endl<<"Rate of interest="<<interestRate<<endl<<"Final Amount: "<<returnValue<<endl;
}


int main()
{
    BankDeposite blank; //if BankDeposite(){} is not created, then it would show error
    blank.showFinalAmount();


    BankDeposite riyad;
    int p,y;
    float r;
    cout<<"Enter p, y, r: "; 
    cin>>p>>y>>r;
    riyad=BankDeposite(p,y,r);
    riyad.showFinalAmount();



    int R;
    cout<<"Enter p, y, R: "; 
    cin>>p>>y>>R;
    BankDeposite supto(p,y,R);
    supto.showFinalAmount();

    return 0;
}