#include <stdio.h>
#define cube(a) a *a *a;
/*#define swap(t, x, y) t = x, x = y, y = t;*/ #define swap(t, x, y) {t = x; x = y; y = t;}
#define max(x, y) x > y ? x : y;
int main()
{
    int a=10, b = 20;
    int t = 0;
    if (a>b) swap(t, a, b);  //a<b
    printf("%d %d\n", a, b);
    int c = cube(b + 2);
    printf("%d\n", c);
    int max_val = max(a++, b++);  //a++ > b++ ? a++ : b++;
    //a++ > b++ ? a++ : b++;
    //10++ > 20++ ? (a=11,b=21) 11++ : 21++; //result=21, but as 21 implemented, and as 21++, so b=22;
    printf("%d %d %d\n", a, b, max_val);
    return 0;
}