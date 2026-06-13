#include <stdio.h>
#include <string.h>
void count_words(char sen[])
{
    int words=0; int k=0;
    for(int i=0; sen[i]!='\0'; i++)
    {
        if(sen[k]==' ')
        {
            k++;
            continue;
        }
        if(sen[i]==' ' && sen[i+1]!=' ' && sen[i+1]!='\0') words++;
    }
    printf("%d\n",words+1);
    return;
}
int main()
{
    char sen[100]="  I love    banglaadesh hehe  o  i  ";
    count_words(sen); // output : 4
}