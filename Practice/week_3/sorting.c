//pseudocode sort:

//selection sort

//from i = 0 to i = (n-1) n being number of array elements to sort, -1 as array names start at 0
//find smallest number between num[i] to num[n-1]  Store value of num[i] in a variable and compare to
//num[i+1], if num[i] is smaller then keep variable the same, otherwise set variable to num[i+1]
//might need new loop from j = i to n-1, just doing the numbers that havent been sorted yet
//swap smallest number with num[i]
//big O = n(n-1)/2 or n^2 when multiplying the brackets and taking the most important term
//best case is also n^2 as if it finds something already sorted it still needs to work through all of irt

//bubble sort

//repeat n-1 times
//  for i from 0 to n-2
//      if num[i] and num[i+1] are out of order
//            Swap them
//      if no swaps
//          quit
//need to repeat everything n-1 times as worst case the last num needs to be in num[0]
//multiply the n-1 outer loop and n-1 inner loop to get big O of n^2, as that's the most important
//best case is just n when things are already in order.

// Recursion

//Above sorts are comparison sorts
//recursion is when a function calls itself

//eg:make pyramid

#include<stdio.h>
#include<cs50.h>

void build(int h);

int main (void)
{
    //get height of pyramid
    int h = get_int("Height: ");
    //need to plug height in to function that references itself
    build(h);
}
//Make function
void build(int h)
{
    if (h <= 0)
    //Less than to avoit issues with negative numbers
    {
        return;
    }
    //The above is to give a stopping point, without it build will run foraever as it will always call upon itself
    //If we set h to be 1, h-1 is 0, which would stop the nested build and go on to print 1 h in the for loop.
    //Larger numbers will just add steps until 0.
    build(h - 1);
    for (int i = 0; i < h; i++)
    {
        printf("#");
    }
    printf("\n");
    //segmentation faults occur when our function touches memory it shouldn't ie gets too big, recurses infinitely
}