// Linked lists are different to arrays as we can't just add 1 and get the next number
// Instead pair each value with a pointer that points to the location of the next location in the list. terminate list by linking NULL
// Can make a data structure that does this:



#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

// We had to temporarily name node after struct so the compiler has something to recognize. Same with adding struct to node inside
// we have whatever data in the node but also have a pointer that points to the whole structure (node in this case)

// How to do this?

int main(void)
{
    // Make list, a pointer to a node, and set it to NULL for now as we haven't done anything with it yet
    node *list = NULL;

    // Make space for an int and a pointer (as defined in struct above) and store pointer in n
    node *n = malloc(sizeof(node));

    // n is a pointer to a chunk of memory big enough to store node. N is not a node, neither is list. They
    // both point to nodes.

    // Safety first!
    if (n == NULL)
    {
        return 1;
    }

    // to store a number, dereference nodepointer n (*n) and set its number part to the number (1 in this case)
    // (*n) = Go to this address and do thing to it. Parentheses are there for order of operations purposes.
    //(*n).number = 1;

    // Can use syntactic sugar to do the same with
    n->number = 1;

    // We can update the nodepointer field similarly
    n->next = NULL;

    // now make list point to the node
    list = n;

    //add a new number to list
    // we can reuse n now since list has taken over
    n = malloc(sizeof(node));

    // Safety, and also cleaning things up
    if (n == NULL)
    {
        free(list);
        return 1;
    }

    // Set second block in list
    n->number = 2;
    n->next = NULL;

    // Make first block point to second block
    list->next = n;

    // AGAIN

    n = malloc(sizeof(node));

    if (n == NULL)
    {
        // free the next one FIRST as freeing list would destroy only pointer to block 2
        free(list->next);
        free(list);
        return 1;
    }

    n->number = 3;
    n->next  = NULL;

    // now we can add box 3 to the end of the list
    list->next->next = n;

    //How to print those numbers?

    printf("%i\n",list->number);
    printf("%i\n",list->next->number);
    printf("%i\n",list->next->next->number);

    //OR use a loop
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }



    //Cleanup

    // Can free everything in reverse order:
    //free(list->next->next);
    //free(list->next);
    //free(list);

    // This loop frees everything in order by using a temporary pointer that is 1 ahead of the freed block
    while (list != NULL)
    {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }

    return 0;
}