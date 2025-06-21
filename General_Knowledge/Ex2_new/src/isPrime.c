#include <stdio.h>
#include "isPrime.h"
#include <math.h>
#include <stdbool.h>

bool isPrime(int number)
{
    if (number < 2) 
    {
        return false;
    }

    for (int i = 2; i <= sqrt(number); i++)
    {
        if (number % i == 0)
        {
            return false;
        }
    }
    
    return true;
}