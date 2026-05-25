#include <stdio.h>
int resultF(int n)
{
    if(n==1)
    {
        return 1;
    }
    int sum=resultF(n-1)+n;
    return sum;
}


int main()
{
    int n=4;
    int result = resultF(n);
    printf("%d",result);

    return 0;
}