// The four adjacent digits in the 1000-digit number that have the greatest product are 9 × 9 × 8 × 9 = 5832.

// 73167176531330624919225119674426574742355349194934
// 96983520312774506326239578318016984801869478851843
// 85861560789112949495459501737958331952853208805511
// 12540698747158523863050715693290963295227443043557
// 66896648950445244523161731856403098711121722383113
// 62229893423380308135336276614282806444486645238749
// 30358907296290491560440772390713810515859307960866
// 70172427121883998797908792274921901699720888093776
// 65727333001053367881220235421809751254540594752243
// 52584907711670556013604839586446706324415722155397
// 53697817977846174064955149290862569321978468622482
// 83972241375657056057490261407972968652414535100474
// 82166370484403199890008895243450658541227588666881
// 16427171479924442928230863465674813919123162824586
// 17866458359124566529476545682848912883142607690042
// 24219022671055626321111109370544217506941658960408
// 07198403850962455444362981230987879927244284909188
// 84580156166097919133875499200524063689912560717606
// 05886116467109405077541002256983155200055935729725
// 71636269561882670428252483600823257530420752963450

// Find the thirteen adjacent digits in the 1000-digit number that have the greatest product. What is the value of this product?

#include <stdio.h>
#include <stdlib.h>

typedef struct frame
{
    int digit;
    struct frame *next;
}
frame;

char *big_number = "7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450";

// frame *make_frames(int count);

int main(void)
{
    // Contaner for products and numbers
    int running_total;
    int current_total = 0;
    int numbers[13];
    int big_number_position = 13;

    // Make and link 13 frames and populate with the first 13 digits
    // current_frame will scan the linked list, left_frame is an anchor for the leftmost 'digit'
    // frame *current_frame = make_frames(0);

    frame *left_frame = malloc(sizeof(frame));
    left_frame->next = NULL;
    left_frame->digit = big_number[0] - 48;
    for (int i = 1; i < 13; i++)
    {
        frame *tmp = left_frame;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = malloc(sizeof(frame));
        tmp = tmp->next;
        tmp->next = NULL;
        tmp->digit = big_number[i] - 48;
    }

    frame *current_frame = left_frame;

    //loop until the end of the big number is reached
    while (big_number[big_number_position] != '\0')
    {
        running_total = 1;

        // Scan current linked list and deposit sum in running_total
        for (int i = 0; i < 13; i++)
        {
            // Segmentation fault here, current frame isn't pointing to anything after one loop (bigNposition is 14. Have to look closer at frame rearranging.)
            running_total = running_total * current_frame->digit;
            current_frame = current_frame->next;
        }

        // Reset current frame to left frame
        current_frame = left_frame;

        // Store product and numbers if the product is the largest found so far
        if (running_total > current_total)
        {
            // Store product
            current_total = running_total;

            // Scan through list and deposit numbers in array for ease of access.
            for (int i = 0; i < 13; i++)
            {
                numbers[i] = current_frame->digit;
                current_frame = current_frame->next;
            }

            // Reset current_frame to left again.
            current_frame = left_frame;
        }

        // Rearrange the list by taking the last frame and storing the next digit in the big array in it.
        left_frame->digit = big_number[big_number_position] - 48;

        // Move current_frame to the end
        while (current_frame->next != NULL)
        {
            current_frame = current_frame->next;
        }

        // link it to the frame with the updated number
        current_frame->next = left_frame;

        // sever loop behing left_frame (even though theres a better way that I see now but I'm committed and there's like 800 more problems on this site so blargh)
        while (current_frame != left_frame)
        {
            current_frame = current_frame->next;
        }
        current_frame->next = NULL;
        current_frame = left_frame;
        big_number_position++;
    }

    // print total and the array of numbers
    printf("Total: %i\n", current_total);

    printf("Sequence: ");
    for (int i = 0; i < 13; i++)
    {
        printf("%i", numbers[i]);
    }
    printf("\n");

    // Free memory

    while (left_frame != NULL)
    {
        current_frame = left_frame->next;
        free(left_frame);
        left_frame = current_frame;
    }

}

// frame *make_frames(int count)
// {
//     frame *tmp = malloc(sizeof(frame));

//     if (count < 12)
//     {
//         // Iterate recursively
//         frame *next_tmp = make_frames(count + 1);
//         tmp->next = next_tmp;

//         // Frames are generated in reverse order so count down instead of up. Convert chars to ints.
//         tmp->digit = (big_number[12 - count] - 48);
//     }
//     else
//     {
//         tmp->next = NULL;
//         tmp->digit = (big_number[12 - count] - 48);
//     }
//     return tmp;
// }