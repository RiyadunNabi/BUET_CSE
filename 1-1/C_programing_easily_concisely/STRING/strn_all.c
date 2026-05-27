#include <stdio.h>

// Function to concatenate two strings up to a specified number of characters
char *strncat_custom(char *dest, const char *src, int n)
{
    int dest_len = 0;
    while (dest[dest_len] != '\0')
    {
        dest_len++;
    }
    int i;
    for (i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[dest_len + i] = src[i];
    }
    dest[dest_len + i] = '\0';
    return dest;
}

// Function to copy characters from one string to another up to a specified number of characters
char *strncpy_custom(char *dest, const char *src, int n)
{
    int i;
    for (i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    for (; i < n; i++)
    {
        dest[i] = '\0';
    }
    return dest;
}

// Function to compare two strings up to a specified number of characters
int strncmp_custom(const char *str1, const char *str2, int n)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0' && i < n)
    {
        if (str1[i] != str2[i])
        {
            return str1[i] - str2[i];
        }
        i++;
    }
    if (i == n)
    {
        return 0;
    }
    return str1[i] - str2[i];
}

int main()
{
    // Test strncat_custom
    char dest1[20] = "Hello ";
    const char *src1 = "world";
    int max_chars1 = 3;
    strncat_custom(dest1, src1, max_chars1);
    printf("After strncat_custom: %s\n", dest1); // Output: Hello wor

    // Test strncpy_custom
    char dest2[20];
    const char *src2 = "This is a test";
    int max_chars2 = 7;
    strncpy_custom(dest2, src2, max_chars2);
    printf("After strncpy_custom: %s\n", dest2); // Output: This is

    // Test strncmp_custom
    const char *str1 = "Hello";
    const char *str2 = "Hellp";
    int num_chars = 4;
    int result = strncmp_custom(str1, str2, num_chars);
    if (result == 0)
        printf("First %d characters are same.\n", num_chars);
    else if (result < 0)
        printf("First %d characters differ (lexicographically smaller).\n", num_chars);
    else
        printf("First %d characters differ (lexicographically larger).\n", num_chars);

    return 0;
}
