#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

int only_digits(string cipher);

void cipher_shift(string plain, int c);

int main(int argc, string argv[])
// remember, [] denotes an array, which can be an array of strings
{
    if (argc == 2 && only_digits(argv[1]) == 0)
        //argc is 2 as it is the name of the function and the first user input. 1 is just function.
        //only_digits starts at 0 and adds 1 whenever it encounters a character that isn't a number.
    {
        int c = atoi(argv[1]);
        //CHECK THE DOCS ^ wouldn't have found this otherwise and it saved a huge headache
        string plaintext = get_string("plaintext: ");
        printf("ciphertext: ");

        cipher_shift(plaintext, c);
        printf("\n");

    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
        //nonzero return values terminate program
    }

}

//check each char if it's a digit or not. number chars integer memory is from 48 to 57.
int only_digits(string cipher)
{
    int validity = 0;
    int length = strlen(cipher);
    for (int i = 0; i < length; i++)
    {
        if (cipher[i] < 48 || cipher[i] > 57)
        {
            validity++;
        }
    }
    return validity;
}

// Uppercase A is 65, lower a is 97
void cipher_shift(string plain, int c)
{
    int l = strlen(plain);
    for (int i = 0; i < l; i++)
    {
        int p = plain[i];
        if (islower(plain[i]))
        {
            p = p - 97;;
            p = (p + c) % 26;
            p = p + 97;
            printf("%c", p);
        }
        else if (isupper(plain[i]))
        {
            p = p - 65;
            p = (p + c) % 26;
            p = p + 65;
            printf("%c", p);
        }
        else
        {
            printf("%c", plain[i]);
        }
    }
}