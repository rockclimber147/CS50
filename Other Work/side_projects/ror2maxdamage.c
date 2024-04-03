// Calculates the maximum potential damage one can achieve in Risk of Rain 2 given the total items and selected item types.

// APR AP rounds             +20%  each
// CRB Crowbar               +75%  each
// DEW Delicate Watch        +20%  each
// FCR Focus Crystal         +20%  each
// LMG Lens-Maker's Glasses  +20%  each MAX 200%
// RNB Runald's Band         +250% each

// Total damage modifier is calculated by product of the individual sums.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct iteration
{
    float total_damage;
    int is_maximum_damage;
    float item_count[6];
    struct iteration *next;
} iteration;

// Store damage modifiers for each individual item
const float APR_DMG = .20;
const float CRB_DMG = .75;
const float DEW_DMG = .20;
const float FCR_DMG = .20;
const float LMG_DMG = .20;
const float RNB_DMG = 2.50;

iteration *create_iteration(int total_item_count, float is_item_selected[], float previous_count[]);

void print_stats(iteration *start, int total_lines, int header);

void free_iterations(iteration *start);

int digit_count_int(int input);

float digit_count_float(float input);

int main(int argc, char *argv[])
{
    if ((argc <= 2) || (argc > 8))
    {
        printf("Usage: ror2maxdamage, item_count, at least 1 of the following item abbreviations: APR CRB DEW FCR LMG RNB\n");
        return 1;
    }

    // Convert item_count (argv[1] to an int)
    int total_item_count = atoi(argv[1]);

    // Make sure item_count is a positive integer
    if (total_item_count <= 0)
    {
        printf("item_count must be a BLAH BLAH BLAH GET FUCKED\n");
        return 2;
    }

    // Array to compare input with accepted item strings
    char *item_types[6];

    item_types[0] = "APR";
    item_types[1] = "CRB";
    item_types[2] = "DEW";
    item_types[3] = "FCR";
    item_types[4] = "LMG";
    item_types[5] = "RNB";

    // Keep track of which items are to be used
    float is_item_selected[6];

    // Make sure all are set to 0 before populating
    for (int i = 0; i < 6; i++)
    {
        is_item_selected[i] = 0;
    }

    // Check argv[] against all possible items, returning if there are no matches
    for (int i = 2; i < argc; i++)
    {
        int found = 0;
        for (int j = 0; j < 6; j++)
        {
            if (strcmp(argv[i], item_types[j]) == 0)
            {
                // Check for matches, make sure user doesn't input a duplicate of any item.
                if (is_item_selected[j] == 0)
                {
                    is_item_selected[j]++;
                    found++;
                }
                else
                {
                    printf("You may select at most one of each item and also eat shit\n");
                    return 3;
                }
            }
        }
        if (found == 0)
        {
            printf("Usage: ror2maxdamage, item_count, at least 1 of trhe following item abbreviations: APR CRB DEW FCR LMG RNB (also eat shit)\n");
            return 1;
        }
    }

    // The above is just to make sure the user inputted everything correctly and to note which items are to be included in the calculation.

    // Set baseline for item amounts, all should start at 0.
    float previous_count[6];
    for (int i = 0; i < 6; i++)
    {
        previous_count[i] = 0.00;
    }
    // Recursively make linked list of maximum damage cases
    iteration *start = create_iteration(total_item_count, is_item_selected, previous_count);

    print_stats(start, total_item_count, 0);

    free_iterations(start);

    return 0;
}

// Create iteration carries forward two things. First is the item_count which is used to count down to termination, second is the array of item totals, to be incremented and evaluated.
iteration *create_iteration(int total_item_count, float is_item_selected[], float previous_count[])
{
    // Account for up to 6 different items before calculating total damage
    iteration *tmp[6];

    for (int i = 0; i < 6; i++)
    {
        // Make space for all item configurations
        tmp[i] = malloc(sizeof(iteration));

        // set item counts to that of previous iteration
        for (int j = 0; j < 6; j++)
        {
            tmp[i]->item_count[j] = previous_count[j];
        }

        // increase counts of only the chosen items
        if (is_item_selected[i] != 0)
        {
            tmp[i]->item_count[i]++;
        }

        // You can have at most 10 Lens Maker's Glasses
        if (tmp[i]->item_count[4] >= 10)
        {
            tmp[i]->item_count[4] = 10;
        }

        // Calculate total damage based on products of item counts and their individual damage multipliers
        tmp[i]->total_damage = 1.00 * (1.00 + (tmp[i]->item_count[0] * APR_DMG)) * (1.00 + (tmp[i]->item_count[1] * CRB_DMG)) * (1.00 + (tmp[i]->item_count[2] * DEW_DMG)) * (1.00 + (tmp[i]->item_count[3] * FCR_DMG)) * (1.00 + (tmp[i]->item_count[4] * LMG_DMG)) * (1.00 + (tmp[i]->item_count[5] * RNB_DMG));
    }

    // Find highest total damage
    float highest_total_damage = 0.00;

    for (int i = 0; i < 6; i++)
    {
        if (tmp[i]->total_damage > highest_total_damage)
        {
            highest_total_damage = tmp[i]->total_damage;
        }
    }

    // Select first iteration which matches the highest total damage
    int match_detected = 0;

    for (int i = 0; i < 6; i++)
    {
        if ((highest_total_damage == tmp[i]->total_damage) && (match_detected == 0))
        {
            tmp[i]->is_maximum_damage = 1;
            match_detected = (i + 1);
        }
    }

    // Free suboptimal configurations
    for (int i = 0; i < 6; i++)
    {
        if (tmp[i]->is_maximum_damage == 0)
        {
            free(tmp[i]);
        }
    }

    // make next iteration if there's still room using stats from the optimal iteration
    if (total_item_count > 1)
    {
        iteration *next_iteration = create_iteration(total_item_count - 1, is_item_selected, tmp[match_detected - 1]->item_count);
        tmp[match_detected - 1]->next = next_iteration;
    }
    else
    {
        tmp[match_detected - 1]->next = NULL;
    }
    // Return iteration that has the maximum damage
    return tmp[match_detected - 1];
}

void print_stats(iteration *start, int total_lines, int header)
{
    // Handle base case
    if (start == NULL)
    {
        return;
    }

    // print a header if it's the first line
    if (header == 0)
    {
        printf("#   total damage  APR CRB DEW FCR LMG RNB \n");
        header++;
    }
    printf("%i", header);

    // Determine spaces and print them so everything lines up
    int spaces = (4 - digit_count_int(header));
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
    header++;

    // Print total damage and add spaces
    printf("%.2f", start->total_damage);
    spaces = (12 - digit_count_float(start->total_damage));
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }

    // Print count and spacing for each item
    for (int i = 0; i < 6; i++)
    {
        printf("%.0f", start->item_count[i]);
        spaces = (4 - digit_count_float(start->item_count[i]));
        for (int j = 0; j < spaces; j++)
        {
            printf(" ");
        }
    }
    // new line
    printf("\n");

    if (total_lines > 1)
    {
        print_stats(start->next, total_lines - 1, header);
    }
    return;
}

void free_iterations(iteration *start)
{
    if (start->next == NULL)
    {
        free(start);
        return;
    }
    else
    {
        free_iterations(start->next);
    }
    return;
}

int digit_count_int(int input)
{
    if (input < 10)
    {
        return 1;
    }
    else if (input < 100)
    {
        return 2;
    }
    else if (input < 1000)
    {
        return 3;
    }
    else
    {
        return 4;
    }
}

float digit_count_float(float input)
{
    if (input < 10)
    {
        return 1;
    }
    else if (input < 100)
    {
        return 2;
    }
    else if (input < 1000)
    {
        return 3;
    }
    else if (input < 10000)
    {
        return 4;
    }
    else if (input < 100000)
    {
        return 5;
    }
    else if (input < 1000000)
    {
        return 6;
    }
    else
    {
        return 7;
    }
}