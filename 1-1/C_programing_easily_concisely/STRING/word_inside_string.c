#include <stdio.h>
#include <string.h>

void selfmade_search(char sen[], char word[])
{
    int slen = strlen(sen), wlen = strlen(word);
    int k = 0;
    while (k < (wlen / 2))
    {
        char t = word[k];
        word[k] = word[wlen - 1 - k];
        word[wlen - 1 - k] = t;
        k++;
    }
    int i = 0, j, count = 0, flag;
    while (sen[i] != '\0')
    {
        j = 0;
        // count=0;
        while (word[j] != '\0' && sen[i] == word[j])
        {
            if (j == 0)
            {
                flag = i;
            }
            count++;
            i++;
            j++;
        }
        if (count == wlen)
            break;
        else
            count = 0;
        i++;
    }
    printf("%d %d \n", count, wlen);

    (count == wlen) ? printf("found %d\n", flag) : printf("NOT FOUND\n");
}

void sudipta_search(char sentence[], char word[])
{
    for (int i = 0; i + strlen(word) <= strlen(sentence); i++)
    {
        int match = 1;
        for (int j = 0; j < strlen(word); j++)
        {
            if (sentence[i + j] != word[strlen(word) - 1 - j])
            {
                match = 0;
                break;
            }
        }
        if (match)
        {
            printf("Found at position: %d\n", i);
            return;
        }
    }
    printf("NOT FOUND\n");
    return;
}
int main()
{
    char sen[100] = "i love solving 101. it does not drive me insane at all";
    char word1[10] = "enasni";
    char word2[10] = "enasni";
    selfmade_search(sen, word1);
    sudipta_search(sen, word2);
    return 0;
}