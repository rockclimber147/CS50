// By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

// What is the 10 001st prime number?

// 44 now

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int check_prime (int num);

int main(void)
{
    // Make container for total amount of primes found, including 2 already
    int prime_total = 1;

    // Start number to check at 3
    int check = 3;

    while (true){
        if (check_prime(check) == 1)
        {
            prime_total++;
        }
        if (prime_total == 100001)
        {
            printf("%i\n", check);
            return 0;
        }
        check = check + 2;
    }
}

int check_prime (int num){
    for (int i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }
    return 1;
}