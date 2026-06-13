#include <stdio.h>
 int factorial(int n)
 {
    if(n==1)
    {
        return 1;
    }
    int fact=n*factorial(n-1);

    return fact;
 }


int main()
{
    int n=4;
    int Fact=factorial(n);
    printf("%d",Fact);

    return 0;
}