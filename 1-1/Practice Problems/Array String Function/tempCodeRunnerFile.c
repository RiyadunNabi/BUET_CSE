void frequency_checker_Best_from_ChatGPT(int arr[], int n)
{
    printf("frequency_checker_Best_from_ChatGPT:\n");
    int count,maxCount,maxElement;
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