#include <stdio.h>
int largest(int arr[], int n)
{

    if(n==1)
    {
        return arr[0];
    }

    for(int i=0; i<n-1;i++)
    {
        if(arr[n-1]>arr[i]);
    }
    return arr[n-1];
}
int main()
{
    int arr[]={2,4,6,8,3};
    int n=5;
    int large=largest(arr,n);
    printf("%d\n",large);
}
