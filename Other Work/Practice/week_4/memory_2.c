#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
    char *s = get_string("s: ");
    // remember char * is the memory location of the first character in a string. functions like
    // string datatype but cs50.h isn't needed.

    char *t = malloc(strlen(s) + 1);
    // making a string t and allocating memory for it using malloc. malloc allocates n bytes and each char
    // in a string takes 1 byte, plus the \0 at the end of the block, hence strlen + 1.

    if (t == NULL)
    {
        return 1;
    }
    // NULL is output by malloc when an issue arises, like not having the memory required

    int n = strlen(s) + 1;

    for (int i = 0; i < n; i++)
    // optimization with n, now strlen is calculated only once as opposed to strlen + 1 times
    // when doing i checks. Note only a comma between declarations
    {
        t[i] = s[i];
    }
    // This copies the values of s into t, but allowing operations to be performed on them separately.
    // just assigning t = s won't work. Can also use strcpy(t, s)

    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }
    // account for user inputting a blank string

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(t);
    // we get s from get_string so allocated memory is removed automatically but we need to free
    // memory used for t at the end

    return 0;
}

//potential errors with malloc

//eg int *x = malloc(3 * sizeof(int)), x[1] = 30, x[2] = 49, x[3] = 25;

// above we didn't zero index our string/array of ints and will overflow our allotted memory
// the above will compile, we can find memory related bugs using valgrind in the command line
// eg. valgrind ./[code]. valgrind will say invalid write of size 4 in the above case
// invalid write as memory outside of what has been allocated is being touched, size 4
// because an int is 4 bytes and what is being assigned in this case.
// it also notices that the allocated memory wasn't freed

// Garbage values

// making an array without filling it and then printing the values of the array will give garbage values
// not initializing a variable would allow viewing of unintended memory

// Pointer Fun

// int *x;
// int *y;

// We can initialize pointers without assigning them yet

// x = malloc(sizeof(int));
// Assign x return value of malloc, an adress of size 4 bytes

// *x = 49;
// "Go to the memory location of x and store 49 there"

// *y = 19;
// "Go to the location of y and store 19 there"
// Issue here as y hasn't been allotted a memeory location with malloc, it will use a garbage
// value