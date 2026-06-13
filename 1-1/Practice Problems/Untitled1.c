#include <stdio.h>
int main()
{
    int T,t,s,b;
    float crr,rrr;
    scanf("%d",&T);
    for(int i=1; i<=T; i++)
    {
        scanf("%d %d %d",&t,&s,&b);
        crr=s/((300-b)/(float)6);
        rrr=(t-s+1)/(b/(float)6);
        printf("%.2f %.2f",crr,rrr);
    }
    return 0;
}
