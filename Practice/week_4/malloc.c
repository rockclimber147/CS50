// Dynamic memory allocation comes from the heap, static (variables/globals etc.) from the stack.
// stack grows up from bottom, heap down from top.
// stdlib.h gives malloc which can allocate a specified amount of memory and give a pointer to it if successful or NULL
// want to check for NULL after mallocing to stop things just in case


#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x = 4;

    // statically obtaining an int

    int *px = malloc(sizeof(int));

    // setting a pointer px to the address returned by malloc that's the size of an integer (4 bytes)

    int x = get_int("integer: ");

    // get an integer from the user

    float stack_array[x];

    // will make an array of floating point numbers of size x on the stack (still statically declared)

    float* heap_array = malloc(x * sizeof(float));

    // malloc returns an address of the specified memory block using variable x. That address is stored in the
    // heap_array pointer which is set to type float. Giant memory block can be treated as an array.

    // this dynamically called memory should be freed up after it's done being used. Use free() function
    // not free()ing can cause a memory leak which will slow down your system
    // free() takes pointer as input. Would want to free(heap_array) when done with it.

    //FREE everything that has been malloced. Don't free things twice. Only free what has been malloced

    eg

    int m;

    // Statically declared integer m. Can change by setting m to be something else.

    int* a;

    // Pointer a declared but not pointing anywhere. a should store address of an int.

    int* b = malloc(sizeof(int));

    // pointer b declared and given the address of a blank memory space that fits an int. can only store things in
    // memory allocated to be by dereferencing b. Unlike with m, no variable assigned to this memory space.
    // will need to free(b) when done

    a = &m;

    // pointer a now has the address of m stored, can change m or *a to change that memory.

    a = b;

    // address in a is set to address in b, now both a and b point to unnamed memory slot

    m = 10:
    *b = m + 2;

    // dereferencing b, putting m + 2 in unnamed memory and making the value 12

    free(b);

    // Makes unnamed memory free to use for other applications. No longer allowed to access w/o mallocing
    // it again, but that will likely give a different address.
}