#include <stdio.h>
#include <stdlib.h>
int main()
{
    int r, c;
    scanf("%d %d", &r, &c);
    int **mtrx = (int **)malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++)
    {
        *(mtrx + i) = (int *)malloc(c * sizeof(int));
    }
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            scanf("%d", *(mtrx + i) + j);
        }
    }
    int is_unique;
    for (int i = 0; i < r; i++)
    {

        for (int k = 0; k < i; k++)
        {
            is_unique = 0;
            
            for (int j = 0; j < c; j++)
            {

                if (*(*(mtrx + i) + j) != *(*(mtrx + k) + j))
                {
                    is_unique = 1;
                    break;
                }
            }
            if (is_unique==0)
            {
                break;
            }
        }
        if (i == 0 || is_unique)
        {
            for (int j = 0; j < c; j++)
            {
                printf("%d ", *(*(mtrx + i) + j));
            }
            printf("\n");
        }
    }
}