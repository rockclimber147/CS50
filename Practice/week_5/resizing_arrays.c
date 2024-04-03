// Coding along the week 5 lecture

// Arrays so far have been used to store a sequence of data, however modifying the amount of spaces in an array can be difficult

#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    // Make and populate an array

    int list1[3];

    list1[0] = 1;
    list1[1] = 2;
    list1[2] = 3;

    for (int i = 0; i < 3; i++)
    {
        printf("%i\n", list1[i]);
    }

    // This prints the items of list in order.

    // Using malloc allocates memory from the heap instead of the stack like above. Above makes an array that is permanently
    // of size 3.

    int *list2 = malloc(3 * sizeof(int));

    // Make sure list can be made and computer isn't out of memory

    if (list2 == NULL)
    {
        return 1;
    }

    list2[0] = 1;
    list2[1] = 2;
    list2[2] = 3;

    // Could also do list2 = 1; (list2 + 1) = 2; ...  Using pointer arithmetic. Does same as above

    // Assume now we want to increase size of list

    int *tmp = malloc( 4 * sizeof(int));
    if (tmp == NULL)
    {
        free(list2);
        return 1;
    }

    // Make tmp values same as list, then add the 4th thing we wanted to add

    for (int  i = 0; i < 3; i++)
    {
        tmp[i] = list2[i];
    }
    tmp[3] = 4;

    // Free the memory list2 points at before making list2 point to tmp

    free(list2);

    list2 = tmp;

    for (int  i = 0; i < 4; i++)
    {
        printf("%i\n", list2[i]);
    }

    // Need to free memory list2 points to again as we made it point to tmp above

    free(list2);

    // There are benefits to both dynamically allocating arrays and statically allocating them. The above modification
    // to list2 is slow, especially with larger arrays

    // We can use realloc to resize arrays much more quickly

    // eg: int * tmp = realloc(list2, 4 * sizeof(int));
    // this will add space for another int at the end of list2 OR will move values in list2 elsewhere where there is room
    // and point to there, freeing the old chunk.
}