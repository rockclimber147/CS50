// Conditionals + for, while, and do while loops.

#include <stdio.h>
#include <cs50.h>

int main(void)
{
//Loops tend to cave some conditional that, when met, terminates the loop
// While loop:
    int x = 0;
    while(x <= 3)
    {
        printf("%i", x);
        x++;
    }
//Output: 0123
//Running from the top down, x starts at 0, prints up until x = 3, x is increased after the print and it's final value is 4.
    printf("%i\n", x);
//Output: 01234

    x = 0;

//for loops
    for(int i = 0; i <= 3; i++)
    {
        printf("%i", x);
        x++;
    }
        printf("%i\n", x);
// Output: 01234
// This does what the while loop does but you can have a completely isolated value in the for()
//had to reset x to 0, trying to printf i will give an error as it isn't declared outside the for()

    x = 0;

//do while
    do
    {
        printf("%i", x);
        x++;
    }
    while( x <= 3);
    printf("%x\n", x);
// Output: 01234
// do while checks the conditions at the bottom of the loop rather than the top
}