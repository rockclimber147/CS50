#include <stdio.h>
#include <cs50.h>


//We can make our own functions by typing (return value) function name(input value)
// for example, a function that doubles it's input:
int double_input(int a)
//can add multiple inputs if separated by commas.
{
    int b = 2 * a;
//Can declare variables in a function,
    return b;
//if we don't reyturn b, b will be stuck in the scope of that function
}
//recall printf just displays in terminal, can't do anything with that. Returning a means we can
//work with the new value of a elsewhere
int main (void)
{
    int a = get_int("Number to double: ");
    a = double_input(a);
//double_input returns twice the value of a, but a needs to be set to that result for the value in main
//to be changed. not having 'a =' in front just gives back the original a.
    printf("%i\n", a);
//prints double a
//prints 4x a, as a had already been doubled before being sent for doubling again in printf
    printf("%i\n", double_input(a));
}
// We can put the body of the new function below main as long as we put the reference above it
// reference being 'int double_input(int a);'. Need a semicolon.