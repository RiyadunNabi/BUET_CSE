#include <stdio.h>
#include <string.h>
void find_substr(char str[], char substr[])
{
    int occurence = 0, j, i;
    for (i = 0; str[i] != '\0'; i++)
    {
        for (j = 0; substr[j] != '\0'; j++)
        {
            if (str[i + j] != substr[j])
            {
                break;
            }
        }
        if (j == strlen(substr))
        {
            occurence++;
        }
    }
    printf("%d", occurence);
    return;
}
int main()
{
    char str[100] = "Bangladesh";  //aaa
    char substr[50] = "desh";     //aa, 2times
    find_substr(str, substr);
}