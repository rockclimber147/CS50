// A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

// Find the largest palindrome made from the product of two 3-digit numbers.

#include <stdio.h>

int check_palindrome(int input);

int main(void)
{
    //Make named variables for intuition
    int palindrome_storage = 0;
    int product = 0;

    // Loop over all values, store highest palindrome
    for (int i = 999; i > 100; i--)
    {
        for (int j = 999; j > i; j--)
        {
            product = i * j;
            if ((check_palindrome(product) == 1) && (product > palindrome_storage))
            {
                palindrome_storage = product;
            }
        }
    }
    printf("%i\n", palindrome_storage);
}

int check_palindrome(int input)
{
    // Using arays and math, need a case for 6 and 7 digits (min 100000 max 1000000)
    int n = 10;
    if (input < 100000)
    {

        // 6 digit case, make array of 6 for individual digits
        int num6[6];
        for (int i = 0; i < 6; i++)
        {
            // digit is acquired by taking mod of n of the input then moving over decimal to isolate digit
            num6[i] = (input % n) / (n / 10);

            // Remove digit from number
            input = input - (num6[i] * (n / 10));

            // Increment n to go to next place
            n = 10 * n;
        }
        for (int i = 0; i < 3; i++)
        {
            // Starting from far left and right, return 0 if numbers aren't the same
            if ((num6[i] - num6[4 - i]) != 0)
            {
                return 0;
            }
        }
        return 1;

    }
    else if (input < 1000000)
    {
        int num7[7];
        for (int i = 0; i < 7; i++)
        {
            num7[i] = (input % n) / (n / 10);
            input = input - (num7[i] * (n / 10));
            n = 10 * n;
        }
        for (int i = 0; i < 3; i++)
        {
            if ((num7[i] - num7[5 - i]) != 0)
            {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}