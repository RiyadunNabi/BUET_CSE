#include <stdio.h>
//printingBits
void printBits(int n)
{
    if(n==0) return;
    printBits(n/2);
    printf("%d",n%2);
    return;
}
//

//set left n bits starting from position p
int setBits_n(int N, int p, int n)
{
    return N | ((1<<n)-1)<<(p-n+1);
}

//clean n bits
int cleanBits_n(int N, int p, int n)
{
    return N & ~(((1<<n)-1)<<(p-n+1));
}

int main()
{
    int x1=170;
    printBits(x1);
    printf("\n");
    //printf("setBits_n of 170 = %d\n",setBits_n(x1,6,3));

    int x2=219;    // Binary number 0b11011011;
    printBits(x2);
    printf("\n");
    //printf("cleanBits_n of 219 = %d",cleanBits_n(x2,7,3)); //output 27
}
/*
unsigned int clear_left_bits(unsigned int num, int p, int n) {
    // Create a mask to clear leftmost n bits starting from position p
    unsigned int mask = (~0u << (p + 1)) | ((1u << (p + 1 - n)) - 1);
    // Apply bitwise AND operation to clear specified bits
    unsigned int result = num & mask;
    return result;
}

int main() {
    unsigned int num = 0b11011011;  // Binary number
    int p = 7;  // Starting position
    int n = 3;  // Number of bits to clear
    unsigned int result = clear_left_bits(num, p, n);
    printf("%u\n", result); // Output: 27 (0b00011011 in binary)
    return 0;
}
*/