//Basics for coding in C as per the start of the week 1 lecture

#include <cs50.h>
#include <stdio.h>
//The above are libraries that the program must be told to include in order to use their functions.

int main(void)
{
//Everything in here is in th main body of the code. Not everything needs to be though, as long as it's referenced somewhere

//We can define variables and assign them values:
    int x = 1;
// x is an integer, and it's value is one. The value is assigned from the right side of the equals sign
// A variable needn't be assigned a value at all for the code to compile
    int y = 2;
    int z = x + y;
// z is assigned the value of x + y, no need to declare the type of data for x and y as it was done earlier
    printf("%i\n", z);
//output: 3
// printf comes from cs50.h. %i tells it the input is an integer, specified outside the quotations
// \n tells printf to make a new line
    printf("%i\n", x + z);
// output: 4
//we can also make a calculation for the single integer. z is 3 and x is 1, no need to define new integer here
    printf("%i, %i\n", x, y);
// output: 1, 2
// printf can take multiple inputs and display the result. This isn't usable for further calculations.

// data types
    int a = 3;
    float b = a;
    printf("%f\n", b);
    //output 3.00000

    float c = 3;
    int d = c;
    printf("%i\n", d);
// output: 3
//integers can't display decimals
    int o = 5;
    int p = 7;
    float q = ( o / p );
    printf("%f\n",q);
//Output : 0.0000000
}