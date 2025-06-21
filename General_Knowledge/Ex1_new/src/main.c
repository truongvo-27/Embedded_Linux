#include <stdio.h>
#include <stdbool.h>

int main()
{
    int a = 10;
    if (isPrime(a) == true)
    {
        printf("Number %d is a Prime number!!!\n", a); 
    } 
    else
    {
        printf("Number %d isn't a Prime number!!!\n", a); 
    }

    int b = 2;
    if (isPrime(b) == true)
    {
        printf("Number %d is a Prime number!!!\n", b);
    }
    else
    {
        printf("Number %d isn't a Prime number!!!\n", b); 
    }
     
    return 0;
}