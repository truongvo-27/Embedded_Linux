#include <stdio.h>
#include "isPrime.h"
#include <math.h>
#include <stdbool.h>

bool isPrime(int number)
{
    if(number < 2) return 0;
    int count = 0;
    for(int i = 2; i < sqrt(number); i++)
    {
        int count = 0;
        if(number % i == 0)
        {
            count++;
        }

    }
    if(count == 2) return 1;
    else return 0;
}