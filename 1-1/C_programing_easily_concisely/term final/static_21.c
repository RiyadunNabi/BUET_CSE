#include <stdio.h>
void swap(int x, int y, int *count)
{
    static int i=0;
    int t=x;
    x=y;
    //y=z;
    i++;
    *count=i;
}
int main()
{
    int a=4, b=5, count;
    swap(a,b,&count);
    printf("%i %i %i\n",a,b,count);
    count=3;
    swap(a,b,&count);
    printf("%i %i %i\n",a,b,count);
}