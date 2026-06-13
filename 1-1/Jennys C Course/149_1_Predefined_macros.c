/********PreDefined Macros********/
#include <stdio.h>

int main()
{
    printf("Date: %s\n", __DATE__);
    printf("Time: %s\n", __TIME__);
    printf("File: %s\n", __FILE__);
    printf("Line: %d\n", __LINE__);
    printf("DNSI: %d\n", __STDC__); // 1 if DNSI, else 0
    printf("\n\n");
    return 0;
}
