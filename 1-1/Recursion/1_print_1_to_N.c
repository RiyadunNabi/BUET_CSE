#include <stdio.h>

 void printNumbersIn(int n)
 {
    if(n==1)
    {
       printf("%d ",n);
       return; 
    }
    printNumbersIn(n-1);
    printf("%d ",n);
 }

 void printNumbersDe(int n)
 {
    printf("%d ",n);
    if(n==1)
    {
    //    printf("%d ",n);
       return; 
    }
    printNumbersDe(n-1);

  /*  if(n<=0)
    {
        return;
    }
    printf("%d ",n);
    printNumbersDe(n-1);*/
 }


int main()
{
    int n=20;
    printNumbersIn(n);
    printf("\n");
    printNumbersDe(n);
    return 0;
}