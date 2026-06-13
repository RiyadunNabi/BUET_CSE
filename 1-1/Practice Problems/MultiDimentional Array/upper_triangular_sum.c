#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n;
    scanf("%d",&n);
    int **mtx=(int **)malloc(n*sizeof(int*));
    for(int r=0; r<n; r++)
    {
        *(mtx+r)=(int*)malloc(n*sizeof(int));
    }
    for(int r=0; r<n; r++)
    {
        for(int c=0; c<n; c++)
        {
            scanf("%d",*(mtx+r)+c);
        }
    }
    int sum=0;
    for(int r=0; r<n; r++)
    {
        for(int c=0; c<n; c++)
        {
            if(r<c)                     //r<c for upper
            {
                sum+=*(*(mtx+r)+c);
            }
        }
    }
    printf("%d",sum);
    
}

//r>c for lower