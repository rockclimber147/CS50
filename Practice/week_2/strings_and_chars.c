#include <stdio.h>
#include <cs50.h>

//strings are an array of chars

int main (void)
{
    string s = "hello";
//Need "" for string, '' is for char
    for(int i = 0; i < 5; i++)
    {
        printf("%c", s[i]);
    }
    printf("\n");
//Output: hello
//Prints individual letters in order from string
    for(int i = 0; i < 5; i++)
    {
        printf("%i ", s[i]);
    }
    printf("\n");
//Output: 104 101 108 108 111
//Converting the individial letters to nmeric ASCII representation
//    int ascii[5];
//    for(int i = 0; i < 6; i++)
//    {
//        ascii[i] = s[i];
//        printf("%i\n", ascii[i]);
//    }
//Converts hello string to string of integers and then prints those integers
//6th number in output is integer value of null character, which is the break in memory at the end
//of a piece of data and before the next, telling the computer where to stop reading from memory
    int a = 104;
    char h = a;
    printf("%c\n", h);
//output: h
// Assigning a character an integer value and printing it as a character returns that character.
    printf("%c\n", a);
//Output: h
//Using printf to read an integer as a character also returns that character
    for(int i = 97; i <= 122; i++)
    {
        printf("%c ", i);
    }
//This prints the alphabet in lowercase!
    printf("\n");
    for(char i = 'A'; i <= 'Z'; i++)
    {
        printf("%c ", i);
    }
//This prints the alphabet in uppercase!!
//so long as characters are enclosed by '' looks like the number memory values can be modified
    printf("\n");
//try to count letters until null value
//Get a string:
    string count = get_string("Count the characters in: ");
//each character is one place in a string so count string places until the integer character is null or 0
    for( int i = 0; count[i] != 0; i++)
    {
        printf("%i\n", i);
    }
}