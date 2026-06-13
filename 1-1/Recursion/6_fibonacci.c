#include <stdio.h>
int fibonacci(int n)
{
    // if(n=0)
    // {return 0;}
    if(n<=1)
    {return n;}

    int result=fibonacci(n-2)+fibonacci(n-1);

    return result;
}

int main()
{
    int result=fibonacci(6);
    printf("%d\n",result);
}