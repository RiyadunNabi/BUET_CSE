#include <stdio.h>
int towerofhanoi(int n)
{
    if(n==1)
    {
        return 1;
    }
    return 2*(3*towerofhanoi(n-1)+1);
}
int main()
{
    int n=4;
    printf("%d",towerofhanoi(n));
}
