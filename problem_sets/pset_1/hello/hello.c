#include <stdio.h>
#include <cs50.h>
int main(void)
{
    // get_string displays what's in quotation marks and assigns what the user inputs to the variable named answer,
    // which is a string.
    string answer = get_string("What's your name? ");
    // The %s indicates what type of data to expect, a string, which was made by the user and assigned to 'answer'
    // printf will display 'hello, ' followed by answer and \n makes a new line.
    printf("hello, %s\n", answer);
}