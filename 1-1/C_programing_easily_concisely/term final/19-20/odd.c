#include <stdio.h>
int main()
{
    int a,b;
    scanf("%d %d",&a,&b);
    if(a%2==0) a++;
    for(int i=a; i<=b; i+=2)
    {
        printf("%d\n",i);
    }
}