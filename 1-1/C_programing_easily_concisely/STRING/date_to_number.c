#include <stdio.h>
void number_from_date(char *date_string)
{
    // Variables to store the day, month, and year
    int day = 0, month = 0, year = 0;

    // Loop through the date string to extract day, month, and year
    int i = 0;
    while (date_string[i] != '\0')
    {
        if (date_string[i] == '-')
        {
            i++; // Move to the next character after '-'
            continue;
        }

        // Convert the characters to integers
        int num = date_string[i] - '0';

        // Based on the position in the date string, assign to day, month, or year
        if (i < 2)
        {
            day = day * 10 + num;
        }
        else if (i < 5)
        {
            month = month * 10 + num;
        }
        else
        {
            year = year * 10 + num;
        }

        i++;
    }

    // Output the separated day, month, and year
    printf("Day: %d\n", day);
    printf("Month: %d\n", month);
    printf("Year: %d\n", year);
}

#include <string.h>
#include <stdlib.h>
void number_from_date_built_in_func(char date_string[])
{
    // Variables to store the day, month, and year
    int day, month, year;

    // Use strtok to tokenize the date string by '-'
    char *token = strtok(date_string, "-");
    if (token != NULL)
    {
        day = atoi(token);
        token = strtok(NULL, "-");
        if (token != NULL)
        {
            month = atoi(token);
            token = strtok(NULL, "-");
            if (token != NULL)
            {
                year = atoi(token);

                // Output the separated day, month, and year
                printf("Day: %d\n", day);
                printf("Month: %d\n", month);
                printf("Year: %d\n", year);

                return;
            }
        }
    }

    printf("Invalid date format!\n");
}

int main()
{
    char date[] = "31-12-2023";
    number_from_date(date);
    number_from_date_built_in_func(date);
}