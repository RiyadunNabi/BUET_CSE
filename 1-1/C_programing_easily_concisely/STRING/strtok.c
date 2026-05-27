#include <stdio.h>
#include <string.h>
int main()
{
    char *str = "- This, a sample-string.";
    char *p;
    p = strtok(str, " ,.-"); // second param has tokens while (p != NULL) {
    while (p != NULL)
    {
        printf("%s\n", p);
        p = strtok(NULL, " ,.-");
    }
}