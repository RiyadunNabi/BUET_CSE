#include <stdio.h>
int pow(int x, int y)
{
    if(y==0)
    {
        return 1;
    }
    // else if(y==1)
    // {
    //     return x;
    // }

    int result=x*pow(x,y-1);
    return result;
}



int main()
{
    int x=3,y=4;
    int result=pow(x,y);
    printf("%d",result);
}