// data passed between functions is passed by value, see case of swap. copies of data
// x and y are copied into swap, but not transferred. Swap operates on the copies.
// memory is a sequence of blocks of data, each having it's own address.
// pointer is nothing more than an address to a location in memory where variables live

#include <stdio.h>
#include <cs50.h>

int main(void)
{

    int k;

    // declarng an integer in a variable k sets aside 4 bytes (the size of an int) of memory and fills that memory with
    // whatever you decide to set k to

    k = 5;

    // 4 byte block og memory now has 5 in it

    int* pk;

    // int* declaration shows that pk has something to do with an integer. pk is just lable, could be anything.
    // pk is not an integer, but a pointer to the memory location of an integer we assigned already.
    // the pointer is 8 bytes or 64 bits and the value it stores is the hex address of variable k

    pk = &k;

    // & next to a variable means the address of that variable. We are assigning pk to the address of k.

    // The value of a pointer is a memory address and the TYPE is the type of data in the address
    // can use pointers to pass actual variables between functions

    // NULL is the name of nothing and it's what pointers should be set to unless there's something else available
    // Making a blank pointer with no value or NULL will point to a garbage value and can be a security flaw.
    // can check if NULL by using == NULL.

    // Can easily make a pointer by EXTRACTING an address using &
    // if int x = 5 then &x is a pointer to an int which has a value of the address of x. That address stores 5.
    // &array[i] is the address of the ith element of array[]. An array is a pointer to the first element of it
    // pointers are just addresses to &x, being the address of x, is a pointer of type whetever x is.

    // DEREFERENCING
    // we go to the reference and change the value there
    // eg we have a pointer to char pc, *pc is the data in the memory address in the variable pc.
    // pc is pointer. Pointer stores address. *pc is data at address

    printf("%i\n", *pk);

    // pk is pointer to memory location of int k. k is 5. dereference pointer pk and get 5.
    // * 'dereference operator' goes to the address referenced by pointer and retrieves the value stored there.
    // dereferencing NULL pointer gives segmentation fault, but is better than getting garbage value/allowing
    // garbage values to be seen.
    // 
}