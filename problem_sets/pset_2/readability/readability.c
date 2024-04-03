#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_spaces(string text);

int count_letters(string text);

int count_sentences(string text);

int main(void)
{
    //prompt user for text
    //Also don't "" your string variables, it will just take whatever name it ia as string input.
    //Also also don't divide two integers and expect a float. Need to divide floats to get any of that
    string text = get_string("Text: ");
    int length = strlen(text);
//Get length of string to limit loops
    float words = count_spaces(text) + 1;
    float letters = count_letters(text);
    float sentences = count_sentences(text);
    float L = (letters / words) * 100;
    float S = (sentences / words) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);

//  Testing after realizing it won't work first go
    printf("words: %f\n", words);
    printf("letters: %f\n", letters);
    printf("sentences: %f\n", sentences);
    printf("L = %f\n", L);
    printf("S = %f\n", S);
    if (grade >= 1 && grade <= 16)
    {
        printf("Grade %i\n", grade);
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int count_spaces(string text)
//Spaces are in between words so spaces + 1 is SHOULD be the word count
{
    int spaces = 0;
    int length = strlen(text);
    for (int i = 0; i <= length; i++)
    {
        if (text[i] == 32)
        {
            spaces++;
        }
    }
    return spaces;
}

int count_letters(string text)
//can use the integer values of lowercase and uppercase range to specify, or include libraries
//from the lab and use uppercase/lowercase tests
{
    int letters = 0;
//Had to CV length definition here as its only in main otherwise
    int length = strlen(text);
    for (int i = 0; i <= length; i++)
    {
        if (isupper(text[i]) || islower(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

int count_sentences(string text)
//Should just count the amount of . ? !
{
    int sentences = 0;
    int length = strlen(text);
    for (int i = 0; i <= length; i++)
    {
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            sentences++;
        }
    }
    return sentences;
}
