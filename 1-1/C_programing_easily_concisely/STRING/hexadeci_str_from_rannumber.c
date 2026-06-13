#include <stdio.h>
void hexadecimal_str_reverse(int n)
{
    char str[1000];
    int i = 0;
    while (n != 0)
    {
        if ((n % 16) <= 9)
        {
            str[i] = '0' + n % 16;
        }
        else
        {
            str[i] = 'A' + n % 16 - 10;
        }
        n /= 16;
        i++;
    }
    str[i] = '\0';
    printf("%s\n", str);
    // int len=0;
    // while(str[len]!='\0') len++;

    for (int j = 0; j < i / 2; j++)
    {
        char t = str[j];
        str[j] = str[i - 1 - j];
        str[i - j - 1] = t;
    }
    printf("%s\n", str);
}
void hexadecimal_str(int n)
{
    int len_hex = 0, n_copy = n;
    while (n_copy != 0) 
    {
        len_hex++;
        n_copy/=16;
    }

    char hex_str[len_hex+1];
    hex_str[len_hex]='\0';
    int i=len_hex-1;
    while(n!=0)
    {
        if(n%16<=9) hex_str[i]= n%16 + '0' ;
        else hex_str[i]= n%16 + 'a' - 10 ;
        i--;
        n/=16;
    }
    printf("%s\n",hex_str);
}
void hexa_builtin(int n)
{
    char hex_str[100];
    sprintf(hex_str, "%x",n);
    printf("sprintf %d = %s\n",n,hex_str);
}
int main()
{
    hexadecimal_str_reverse(1530);
    hexadecimal_str(1530);
    hexa_builtin(1530);

}