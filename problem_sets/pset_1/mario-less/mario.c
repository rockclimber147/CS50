#include <stdio.h>

#include <cs50.h>

int main (void)
{
    //put do while loop for an integer between 0 and 9 (not including those) to satisfy input conditions
    // h can't be declared inside the do while loop as while loop needs to reference it
    int h;
    int i;
    i = 1;
    do
    {
        h = get_int("Height: ");
    }
    //It will loop back until the condition is set. Specify everything but the cindition.
    while (h < 1 || h > 8);

    while (i <= h)
    {
        for (int n = 0; n < (h - i); n++)
        {
            printf(" ");
        }
        for (int m = 0; m < i; m++)
        {
            printf("#");
        }
        i++;
        printf("\n");
    }
}