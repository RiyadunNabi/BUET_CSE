#include <stdio.h>
#include <string.h>

int main()
{
    char sentence[100]="I love Hello world.";
    char word[10]="dlrow";

    for(int i=0; i<strlen(word)/2;i++)
    {
        char c=word[i];
        word[i]=word[strlen(word)-1-i];
        word[strlen(word)-1-i]=c;        
    }
    printf("word=%s\n",word);

    int i=0;
    while(sentence[i]!='\0')
    {
        int j=0;
        //int k=i;
        while (word[j])
        {
            if(sentence[i+j]==word[j])
            {
                //k++;
                j++;
                continue;
            }
            else break;
        }
        if((j)==strlen(word))
        {
            printf("found at: %d",i);
            return 0;
        }
        i++;  
    }
    printf("Not found %d",strlen(word));
    return 0;
}