//arrays allow you to store multiple values in one place holder
#include<stdio.h>
#include<cs50.h>

int main(void)
{
    int array[3];
//Like making a variable, but square brackets denote array and number within designates amount of values to store
    array[0] = 50;
    array[1] = 60;
    array[2] = 60;
// can assign values within arrays individually, must start at 0. No choice to start at other number
// array stores all of the same data type, no need to redeclare
    printf ("%i\n", array[0] + array[2]);
//Output: 110
//Right now just treating like regular variables
//Can assign also with something like array[0] = get_int("Put in array: )
//This makes reentering values easier but not good enough
//Can make faster with for loop:
    for(int i = 0; i < 3; i++)
    {
        array[i] = 50 + i;
        printf("%i\n", array[i]);
        //Output: 50 51 52
    }
    printf("%i\n",array[0] + array[1] +array[2]);
//Output: 153
//3 is an arbitrary cutoff, can be a variable as well.

// Arrays can store characters as well, and printf can convert them to their numerical binary values in ASCII
    char c1 = 'Y';
    char c2 = 'E';
    char c3 = 'S';
// Need '' around letter
    printf("%c%c%c\n", c1, c2, c3);
//Output: YES
    printf("%i %i %i\n", c1, c2, c3);
//Output: 89 69 63
//printf() can convert automatically, or tell explicitly: printf("%i", (int) c1);
}