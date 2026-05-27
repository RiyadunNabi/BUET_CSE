#include <stdio.h>
#include <stdlib.h>
//string from number
void my_sprintf(char *dst,int n_scr)
{
    //sprintf
    sprintf(dst,"%d",n_scr);
    printf("sprintf = %s\n",dst);
}
void my_itoa(char dst[],int n_scr)
{
    dst = itoa(n_scr);
}

//number from string
void my_sscanf(char src[],int n_dst)
{
    sscanf(src,"%d",&n_dst);
    printf("sscanf = %d",n_dst);
}
void my_atoi(char src[],int n_dst)
{
    n_dst=atoi(src);
    printf("atoi = %d",n_dst);
}

int main()
{
    char src[100]="2205076";
    char dst[100];
    int n_scr=2205076,n_dst;

    //my_sprintf(dst,n_scr);
    my_sscanf(src,n_dst);

    //my_atoi(src,n_dst);

}