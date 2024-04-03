#include <stdio.h>
#include <cs50.h>



//hexadecimal is base 16, A to F after 9, F is 15 as we count 0.
//8 bits in binary is 255, first f in hex is first four bits, second is second half.
//conventionally, hex is shown as 0x[number]
int main(void)
{
    int n = 50;

    //ints are stored s 4 bytes or 32 bits in memory
    //variable is stored as n and it has an address in memory (0xabc etc.)

    printf("%i\n", n);

    //single ampersand is address of an operator

    int *p = &n;

    //asterisk denotes the variable stores an adress, in this case the address of an integer.
    //p is a pointer, so specify type of value whose address you're storing and assign an address

    printf("%p\n", p);

    //this will print the memory address of n, no need star as it is in the declaration, like no need repeat int

    printf("%p\n", &n);

    //can also just specify print a pointer of an address directly w/o making a variable
    //address isn't always the same every time you run, computer is doing other things and moving things around
    //can control where things go and see, can mess things up that way
    //star used to declare pointer, dereference pointer, multiply
    //pointer p always takes up 8 bytes (64 bits) to be able to count high enough to reference
    //everything. Pointer is a number in an address that refers to another address
    //eg apartment with a billion mailboxes, they can have numbers or numbers that are the address
    //of a different mailbox.

    //strings are an array of characters, datatype doesn't actually exist in c. cs50.h defines string

    string s = "Hello!";
    printf("%s\n", s);

    // H e l l o \0 in array
    //H = 0x123 ... \0 = 0x128
    //s is a variable of type string, it's a pointer to the first character in s. Last
    //character has \0 at the end
    //string s == char *s, s being first character in string
    //with \0 at the end realy just need start and end

    char *t = "Hello!";
    printf("%s\n", s);

    //can do this without cs50 library, computer looks at starting letter in memory and continues until it reaches the \0
    //%s comes with printf as a string is programmer terminology

    //typedef char *string; is a one line function that brings 'string' datatype into existence
    //double quotes "" tell compiler that what's in between is a string and to add \0 at end

    //s is address of first char in a string

    char *s = "HI!";
    printf("%c\n", *s);
    printf("%c\n", *(s + 1));
    printf("%c\n", *(s + 2));

    //* before s in above is dereference operator, means go to that address
    //This will still print HI!, do dame thing as s[n]

    int num[] = {1,2,3};
    printf("%i\n", *numbers);
    printf("%i\n", *(numbers + 1));
    printf("%i\n", *(numbers + 2);

    //can also do this with any other array
    //ints take 4 bytes, but pointer jumps memory chunks, no need to do +4, +8 etc. as compiler knows
    //arrays can be treaated as pointers to their first address
}