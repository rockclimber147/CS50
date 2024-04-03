//The sum of the squares of the first ten natural numbers is,

//The square of the sum of the first ten natural numbers is,

//Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is .

//Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.

#include <stdio.h>

int main(void)
{
    int sum_squares = 0;

    int square_sum = 0;

    int difference = 0;

    for (int i = 0; i <= 100; i++)
    {
        sum_squares = sum_squares + (i * i);
        square_sum = square_sum + i;
    }

    square_sum = square_sum * square_sum;

    difference = square_sum - sum_squares;

    printf("Sum of squares: %i, Square of sum: %i, Difference: %i\n", sum_squares, square_sum, difference);
}