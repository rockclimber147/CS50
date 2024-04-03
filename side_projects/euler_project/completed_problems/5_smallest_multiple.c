// 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

// What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

#include <stdio.h>

int main(void)
{
    int count = 0;

    // Not sure what upper bound to put here but it does work.
    for (int i = 20; 1 < 1000000; i = i + 20)
    {
        count = 0;
        for (int j = 2; j <= 20; j++)
        {
            if (i % j == 0)
            {
                // If divisible then increment count
                count++;
            }
            // Condition is met only when count is 19
            if (count == 19)
            {
                printf("%i\n", i);
                return 0;
            }
        }
    }
    return 1;
}