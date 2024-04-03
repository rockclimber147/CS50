#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int validate_cipher(string cipher);

int main(int argc, string argv[])
{
    if (argc != 2)
        //2 arguements: filename and cipher, more or less = fail
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (validate_cipher(argv[1]) != 0)
        //validate_cipher returns 0 iaoi all all alphabet characters are used once
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }
    else
    {
        string plain = get_string("plaintext: ");
        printf("ciphertext: ");
        string c = argv[1];
        //I thought that calling argv[1][n] would go into the string argv[1] but I guess not?
        //Need to convert the plaintext string chars to their equivalent positions in the cipher
        //Need to preserve upper and lowercase, as well as punctuation
        //find if a character, 2 operations for upper and lowercase
        int letter = 0;
        int plain_length = strlen(plain);
        for (int i = 0; i < plain_length; i++)
        {
            if (islower(plain[i]))
                //Convert lowercase a - z to 0 - 26
            {
                int low = plain[i];
                low = low - 97;
                //converts lowercase to it's equivalent integer placement in alphabetical order
                plain[i] = tolower(c[low]);
            }
            else if (isupper(plain[i]))
            {
                int up = plain[i];
                up = up - 65;
                plain[i] = c[up];
            }
            //if neither upper or lower, don't change
            printf("%c", plain[i]);
        }
    }
    printf("\n");
}

int validate_cipher(string cipher)
//cipher will be argv[1] as it's second string after filename
//argv must be exactly 26 chars and have one of each letter
//make cipher all caps then sum each char and check against sum (65...90) = 2015
//Need to MAKE SURE no multiple duplicates, bbccefg.... adds to 2015 too.
{
    int length = strlen(cipher);
    int sum_char = 0;
    int r = 0;
    if (length == 26)
        //accounts for too long/not long enough
    {
        for (int i = 0; i < length; i++)
        {
            cipher[i] = toupper(cipher[i]);
            //cipher forced to uppercase(really want all same case)
            sum_char = sum_char + cipher[i];
            //for loop makes sure cipher[i] is unique by checking it against all the other places
            for (int n = 1; n < (25 - i); n++)
                //Had to set n to 1 otherwise check chars against selves and tank things.
            {
                if (cipher[i] == toupper(cipher[i + n]))
                {
                    r++;
                    return r;
                }
            }
        }
        if (sum_char != 2015)
            //anything other than 2015 means not all capital letters are present
        {
            r++;
        }
    }
    else
//Forgot this else, since r was set to zero initially not 26 chars would bypass above checks
//and r would still be 0
    {
        r++;
    }
    return r;
}