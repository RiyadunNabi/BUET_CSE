#include <stdio.h>
/**************************************************************************************************************************************/
void printArray(int a[],int n)
{
    for(int i=0; i<n; i++)
    {
        printf("%d\t",a[i]);
    }
    printf("\n");
    return;
}
/**************************************************************************************************************************************/
//i=0; i<n; j=0; j<i; a[j]>a[i]  //insertion sort   (better for small array or nearly sorted array)                        
/*   j<i always     will use it finally                                     For small arrays or arrays that are nearly sorted, 
                                                                            insertion sort tends to perform quite well because it has a best-case time complexity of O(n)
                                                                            when the array is already sorted or nearly sorted.
                                                                            However, its worst-case time complexity is O(n^2),
                                                                            which means it can be inefficient for larger arrays or arrays with a more random distribution of elements.*/
//i=0; i<n; j=i; j<n; a[i]>a[j]  //selection sort  (j=i+1 recomended)
 /*    i<j always   */                                                      /*selection sort also has a time complexity of O(n^2), 
                                                                            both in the best-case and worst-case scenarios.
                                                                            However, selection sort typically performs more comparisons than insertion sort, 
                                                                            so it may be slightly less efficient in practice.*/
                                                                            /*In terms of space complexity, both algorithms have a space complexity of O(1) 
                                                                            since they sort the array in place without requiring additional memory proportional to the size of the input array.*/
void Increasing_i(int a[], int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=i; j<n; j++)
        {
            if(a[i]>a[j])
            {
                int t=a[i];
                a[i]=a[j];
                a[j]=t;

            }
        }
    }
}

/*Bubble sort, not actually*/ //will use it
void Increasing_n(int a[],int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(a[i]<a[j])       //j<i
            {
                int t=a[i];
                a[i]=a[j];
                a[j]=t;
            }
        }
    }
}
/*bubble sort*/
void BubbleSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)                //i<n
    {
        for (int j = 0; j < n - i - 1; j++)              //j<n-1
        {
            if (a[j] > a[j + 1])             //change
            {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}

//increasing
void increasing_my(int a[],int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<i; j++)
        {
            if(a[i]<a[j])
            {
                int t=a[i];
                a[i]=a[j];
                a[j]=t;

            }
        }
    }
}

/**************************************************************************************************************************************/
//i=0; i<n; j=0; j<i; a[j]<a[i]  //insertion     // j<i
//i=0; i<n; j=i; j<n; a[i]<a[j]                  // i<j
void Decreasing_i(int a[],int n)           
{
    for(int i=0; i<n; i++)
    {
        for(int j=i; j<n; j++)
        {
            if(a[i]<a[j])
            {
                int t=a[i];
                a[i]=a[j];
                a[j]=t;

            }
        }
    }
}
void Decreasing_n(int a[],int n)    //will use it
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(a[i]>a[j])
            {
                int t=a[i];
                a[i]=a[j];
                a[j]=t;

            }
        }
    }
}
/**************************************************************************************************************************************/
int main()
{
/**************************************************************************************************************************************/
    printf("Increasing order:\n");
    int a[10] = {4, 6, 2, 1, 3, 5};
    int n=6;
    Increasing_n(a,n);
    printArray(a,n);

/**************************************************************************************************************************************/
    printf("Decreasing order:\n");
    int a2[10] = {6, 4, 2, 1, 3, 5};
    int n2=6;
    Decreasing_n(a2,n2);
    printArray(a2,n2);
/**************************************************************************************************************************************/
    return 0;

}