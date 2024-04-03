#include <stdio.h>

#include <cs50.h>

void bricks(int n);

int main(void)
{
    //put do while loop for an integer between 0 and 9 (not including those) to satisfy input conditions
    // h can't be declared inside the do while loop as while loop needs to reference it
    int h;
    int n;
    n = 1;
    do
    {
        h = get_int("Height: ");
    }
    //It will loop back until the condition is set. Specify everything but the cindition.
    while (h < 1 || h > 8);

    while (n <= h)
    {
        //I made it <= so that n represents number of bricks accurately
        for (int i = 1; i <= (h - n); i++)
        {
            printf(" ");
        }
        bricks(n);
        printf("  ");
        bricks(n);
        n++;
        printf("\n");
    }
}

//prints a brick until the number of bricks reaches n
void bricks(int n)
{
    for (int i = 1; i <= n; i++)
        //code works without curly brackets in for loop as there's only one line of code
        //style50 wants me to add them though
    {
        printf("#");
    }
}
