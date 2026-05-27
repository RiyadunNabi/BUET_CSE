#include <stdio.h>
/*
In the my_strchr function, the str parameter is declared as const char* instead of just char* for two main reasons:
1. Prevent Modification of Input String: By declaring str as const char*, it communicates to the caller that the function does not intend to 
   modify the input string. This is a form of documentation for the function's behavior and helps ensure that the function doesn't inadvertently
   alter the string passed to it.
2. Compatibility with Literal Strings: In C, string literals are arrays of const char, meaning they cannot be modified. By accepting const char*,
   the function can accept both string literals and non-const character arrays, providing more flexibility in usage.

   However, it's worth noting that if the function were intended to modify the string, the parameter should indeed be declared as char*,
   allowing the function to change the contents of the string. But since strchr doesn't modify the input string, it's appropriate to declare
   str as const char*.
   So, using const char* as the parameter type for str helps ensure clarity, prevent unintended modifications, and enables compatibility with
   both string literals and non-const character arrays.
*/
char *my_strchr(const char *str, char ch)
{
    while (*str != '\0')
    {
        if (*str == ch)
        {
            return (char *)str; // Found the character, return its address
        }
        str++; // Move to the next character
    }
    if (ch == '\0')
    {
        return (char *)str; // Return pointer to null terminator if searching for null terminator
    }
    return NULL; // Character not found
}
int main()
{
    const char str[] = "Hello, World!";
    char ch = 'o';
    char *result = my_strchr(str, ch);

    if (result != NULL)
    {
        printf("'%c' found at index %ld\n", ch, result - str);
    }
    else
    {
        printf("'%c' not found\n", ch);
    }
    return 0;
}
