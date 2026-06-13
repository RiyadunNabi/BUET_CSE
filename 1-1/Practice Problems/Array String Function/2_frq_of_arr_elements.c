#include <stdio.h>
void frequency_checker_First_idea(int arr[], int n)
{
    printf("frequency_checker_First_idea:\n");
    int i, m, count, flag;
    int maxCount=0,maxElement;
    for (i = 0; i < n; i++)
    {
        flag=0;
        for (int j = 0; j < i; j++)
        {
            if (arr[i] == arr[j])
            {
                flag++;
                break;
            }
        }
        if (flag)
        {
            continue;
        }
        count=1;
        for (m = i + 1; m < n; m++)
        {
            if (arr[i] == arr[m])
            {
                count++;
            }
        }
        
        if(maxCount<count)
        {
            maxElement=arr[i];
            maxCount=count;
        }
        printf("%d : %d times\n", arr[i], count);
    }
    printf("%d\n",maxElement);
}

void frequency_checker_Best_from_ChatGPT(int arr[], int n)
{
    printf("frequency_checker_Best_from_ChatGPT:\n");
    int count,maxCount=0,maxElement;
    for(int i=0; i<n; i++)
    {
        if(arr[i]==-1)
        {
            continue;
        }
        count=1;
        for(int m=i+1; m<n; m++)
        {
            if(arr[i]==arr[m])
            {
                count++;
                arr[m]=-1;
            }
        }
        if(maxCount<count)
        {
            maxElement=arr[i];
            maxCount=count;
        }
        printf("%d : %d times\n",arr[i],count);
    }
    printf("%d\n",maxElement);

}

int main()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    frequency_checker_First_idea(arr,n);
    frequency_checker_Best_from_ChatGPT(arr,n);
    return 0;
}