#include <stdio.h>
int Pos_Neg_minus(int n)
{
    return (-n)>>31;
}
int Pos_Neg_negation(int n)
{
    return (~n)>>31;
}
int main()
{
    int a1=5,a2=-7;
    printf("%d\n",Pos_Neg_minus(a1));
    printf("%d\n",Pos_Neg_minus(a2));

    printf("%d\n",Pos_Neg_negation(a1));
    printf("%d\n",Pos_Neg_negation(a2));
}