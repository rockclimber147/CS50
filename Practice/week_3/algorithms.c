//efficiency == minimum steps to do thing, min runtime
//see phone book lookup on first lecture.  Big O notation gives on the order of steps > fermi estimate
//capital omega used to represent lower bound, while big o is upper. big theta is when O == omega
//functions stop when they first are told to return a value

//searches:

//strings can't be compared with == as they aren't primitive datatypes (int, float, etc.). Use string comparing
//function from string.h
//BOOLEAN 0 IS FALSE ALWAYS

#include<stdio.h>
#include <cs50.h>

int main(void)
{
    int sample_ints[] = {4, 6, 2, 7, 5, 0, 1, 9};
    int n = get_int("search for number between 1 and 9: ");
    //If you know what all values are going to be in an array beforehand ^
    for (int i = 0; i < 8; i++)
    {
        if (sample_ints[i] == n)
        {
            printf("found %i\n", n);
            return 0;
            //This^ will stop the search when if condition is met
        }
    }
    printf("Number not found :(\n");
    return 1;
}