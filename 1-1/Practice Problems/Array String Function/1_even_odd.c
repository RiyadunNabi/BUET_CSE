#include <stdio.h>

void arrEvenOdd(int arr[],int n)
{
    int arrEven[n],arrOdd[n],j=0,k=0;
    for(int i=0; i<n; i++)
    {
        if(arr[i]%2==0)
        {
            arrEven[j]=arr[i];
            j++;
        }
        else
        {
            arrOdd[k]=arr[i];
            k++;
        }
    }
    /* arrEven[j]='\0';
    arrOdd[k]='\0'; */

    printf("Even elements: {");
    for(int a=0; a<j; a++)
    {
        printf("%-4d",arrEven[a]);
    }
    printf("}\n");

    printf("Odd elements: {");
    for(int b=0; b<k; b++)
    {
        printf("%-4d",arrOdd[b]);
    }
    printf("}\n");
}


int main()
{
    int n;
    scanf("%d",&n);
    int arr[n];
    for (int i=0; i<n; i++)
    {
        scanf("%d",&arr[i]);
    }
    arrEvenOdd(arr,n);
}