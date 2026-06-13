/***********************SWITCH*********************************/
/*
switch(expression) //int or char value
{
    case value-1: or case 'a':
                block of statement;
                break;
    case value-2:
                block of statement;
                break;

    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
            printf("Vowel\n");
            break;

    default :
            default statement;
}
*/
/* EXPRESSION:
if int a=5, then switch(a)=switch(5)
if switch(10.2) -> switch(10)
if int a=1,b=3, switch(a+b)=switch(4);
if float a, switch(a)--> error
if int a, float b, switch(a+b)--> error

if switch(a>b), then if a>b is true then, (a>b)==1 ,, switch(1), otherwise switch(0).
*/

#include <stdio.h>
int main()
{
    int a = 1, b = 2, c = 6;

    switch (a > b && a > c)
    {
    case 1:
        printf("a is the boss");
        break;

    case 0:
        printf("a is not boss");
        break;
    }
}