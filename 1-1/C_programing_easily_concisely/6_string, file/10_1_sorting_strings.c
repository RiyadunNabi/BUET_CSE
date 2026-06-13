#include <stdio.h>
#include <string.h>

int main()
{
    char *list[100] = {"hello", "australia", "bangladessh", "america"};
    int n = 4;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)        //j<i
        {
            if (strcmp(list[j], list[i]) > 0)
            {
                char *temp;
                temp=list[i];
                list[i]=list[j];
                list[j]=temp;
                // strcpy(temp, list[i]);      //doesnt work
                // strcpy(list[i], list[j]);
                // strcpy(list[j], temp);
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", list[i]);
    }
}