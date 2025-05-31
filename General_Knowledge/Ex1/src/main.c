#include <stdio.h>
#include "isPrime.h"

int main()
{
    int a = 10;
    int b = 13;
    
    if(isPrime(a) == 0)
        printf("Number %d isn't a Prime number!!!\n", a);
    else
        printf("Number %d is a Prime number!!!\n", a);

    if(isPrime(b) == 0)
        printf("Number %d isn't a Prime number!!!\n", b);
    else
        printf("Number %d is a Prime number!!!\n", b);   
    return 0;
}