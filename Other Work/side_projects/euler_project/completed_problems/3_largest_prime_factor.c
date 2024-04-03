// The prime factors of 13195 are 5, 7, 13 and 29.

// What is the largest prime factor of the number 600851475143 ?

#include <stdio.h>

int check_prime (long num);

void largest_prime_factor (long i0, long input);

int main(void)
{
    largest_prime_factor(2, 600851475143);
}

int check_prime (long num)
{
    // Check num against all lower integers, if it divides evenly at any point then it isn't a prime
    for (long i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }

    // Return 1 if prime
    return 1;
}

void largest_prime_factor (long i0, long input)
{
    for (long i = i0; i <= input; i++)
    {
        if ((check_prime(i) == 1) && (input % i == 0))
        {
            printf("%li\n", i);
            largest_prime_factor(i, input / i);
            return;
        }
    }
    return;
}