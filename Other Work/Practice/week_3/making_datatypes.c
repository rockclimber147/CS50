//We can make our own datatypes so long as we define what they are

#include<stdio.h>
#include <cs50.h>
#include <string.h>

typedef struct
{
    string name;
    int number;
}
person;
//This assigns the name and number strings to the 'person' data structure
//if we want B and T to be encapsulated with their numbers we can do the following:

int main(void)
{
    string s = get_string("Bill or Ted? ");
    person people[2];

    people[0].name = "Bill";
    people[0].number = 67;
    //"" for string, if around an int it won't be recognized as such

    people[1].name = "Ted";
    people[1].number = 47;

    for (int i = 0; i < 2; i++)
    {
        if (strcmp(people[i].name, s) == 0)
        {
            printf("%i\n", people[i].number);
            //number part of new datastructure is a int so call an int
            return 0;
        }
    }
    printf("Not in list :(\n");
    return 0;
}