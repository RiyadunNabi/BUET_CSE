#include <stdio.h>

void insert_el(int a[], int n, int i, int x) // dynamic size of a=n //at i th index, insert x
{
    for (int j = n; j >= i; j--)
    {
        a[j] = a[j - 1];
    }
    a[i - 1] = x;
}

void remove_el(int a[], int n, int i) //
{
    for (int j = i - 1; j < n - 1; j++)
    {
        a[j] = a[j + 1];
    }
}

int main()
{
    int a[10] = {1, 2, 3, 4, 5};
    int n = 5;
    printf("sizeof(a)=%d\n", sizeof(a));

    insert_el(a, 5, 3, 10);
    printf("After inserting:\n");
    for (int i = 0; i < n + 1; i++)
    {
        printf("%d\n", a[i]);
    }

    remove_el(a, 5 + 1, 3);
    printf("After removing:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", a[i]);
    }

    return 0;
}
