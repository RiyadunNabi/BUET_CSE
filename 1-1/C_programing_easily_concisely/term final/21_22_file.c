#include <stdio.h>
#include <stdlib.h>
int main()
{
    FILE *fp_in = fopen("21_22_input.txt","a+");
    if(fp_in==NULL) exit(1);

    int num=0, sum=0;
    for(int i=0; i<10; i++)
    {
        fscanf(fp_in, "%d", &num);
        printf("%d\n",num);
        sum+=num;
    }
    printf("%d",sum);
    fseek(fp_in,0,SEEK_END);
    
    fprintf(fp_in, "\n%d",sum);
    fclose(fp_in);
}