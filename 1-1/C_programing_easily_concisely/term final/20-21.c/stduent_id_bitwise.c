#include <stdio.h>

void getcode(int stud_id)
{
    int serial=stud_id%1000;
    stud_id=stud_id/1000;

    int dept=stud_id%100;
    stud_id=stud_id/100;

    int year=2000+stud_id%100;

    printf("%d %d %d\n",year,dept,serial);

    int code=0;
    code=year|code;
    code=code<<9;
    code=code|dept;

    code=code<<9;
    code=code|serial;

    printf("%d\n",code);
}

void getstud_id(int code)
{
    int serial=((1<<9) - 1)&code;
    code=code>>9;
    int dept=((1<<9)-1)&code;
    code=code>>9;
    int year=((1<<13)-1)&code - 2000; // %100;

    int stud_id=100000*year + 1000*dept + serial;
    printf("%d\n",stud_id);
}

int isPolindrom(int x)
{
    int x2=x;
    int reverse=0;
    while(x2)
    {
        reverse= x2%10 + 10*reverse ;
        x2/=10;
    }
    return x==reverse;
}

int main()
{
    getcode(2205128);
    getstud_id(530057856);

    printf("%d\n",isPolindrom(1234321));
}