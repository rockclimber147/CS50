
#include <cs50.h>

#include <stdio.h>

int main(void)
{
    //Define variables
    long card_number;
    //Fraction of placement of number, used to divide card by to get individual numbers
    int place;
    //The single digit number in a given place on the card number
    int parity = 1;
    //to count up with place, determine if place is even or odd
    int sum_even = 0;
    int sum_odd = 0;
    int digit_one;
    int digit_two;
    int total_digits = 0;
    do
    {
        card_number = get_long("Card Number: ");
    }
    while (card_number < 0 || card_number > 9999999999999999);
    //Find first and second digit by repeatedly dividing by 10. File isn't float so no decimals
    long z = card_number;
    while (z >= 100)
    {
        z = z / 10;
        //added total digits counter. It's off by two but really just needs to check if the number
        //has more than 13 (or 11 in its case). All cases still work though, no 2 digit cards today
        total_digits++;
    }
    digit_one = z / 10;
    digit_two = z % 10;
    //Loop to find placement and parity, and sum all even and odd numbers
    for (long n = 10; n <= 10000000000000000; n = n * 10)
    {
        place = card_number % n / (n / 10);
        if (parity % 2 == 1)
        {
            sum_odd = sum_odd + place;
        }
        else
        {
            place = place * 2;
            if (place > 9)
            {
                place = place % 10 + 1;
            }
            sum_even = sum_even + place;
        }
        parity++;
    }
    //determine validity and continue to find brand
    if ((sum_even + sum_odd) % 10 == 0 && total_digits > 10)
        //Had to add parity as it counts digits and had to exclude numbers with fewer than 13
    {
        if (digit_one == 3 && (digit_two == 4 || digit_two == 7))
        {
            printf("AMEX\n");
        }
        else if (digit_one == 5 && (digit_two > 0 && digit_two < 6))
        {
            printf("MASTERCARD\n");
        }
        else if (digit_one == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}