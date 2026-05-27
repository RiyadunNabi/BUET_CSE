#include <stdio.h>
#include <string.h>

int main()
{
    char lines[100][1000];
    char modified_lines[100][1000];
    char longest_line[1000];
    int longest_length = 0;
    int num_lines = 0;

    // Taking input lines
    printf("Enter lines (Enter 'done' on a new line to finish):\n");
    while (1)
    {
        gets(lines[num_lines]);
        if (strcmp(lines[num_lines], "done") == 0)
            break;
        num_lines++;
    }

    // Stripping leading and trailing spaces, finding the longest line
    printf("\nModified lines:\n");
    for (int i = 0; i < num_lines; i++)
    {
        char *start = lines[i];
        char *end = lines[i] + strlen(lines[i]) - 1;
        // Strip leading spaces
        while (*start == ' ' || *start == '\t')
            start++;
        // Strip trailing spaces
        while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
            end--;
        *(end + 1) = '\0'; // Null-terminate the modified line
        strcpy(modified_lines[i], start);
        printf("Line %d: %s\n", i + 1, modified_lines[i]);

        // Finding the longest line
        int length = strlen(modified_lines[i]);
        if (length > longest_length)
        {
            longest_length = length;
            strcpy(longest_line, modified_lines[i]);
        }
    }

    // Outputting longest line and its length
    printf("\nThe longest line is: '%s'\n", longest_line);
    printf("Its length is: %d\n", longest_length);

    return 0;
}

