#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        //argv is user input, argv[0] is program so argv[1+] are the candidates typed by the user
        //The names of the candidates are stored in the candidate structture 'candidates'.name
        candidates[i].votes = 0;
        //this sets the votes to zero before the counting starts
    }

    int voter_count = get_int("Number of voters: ");
    //we set number of voters

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
            //If the vote function doesn't recognize the name that was inputted as one from the
            //candidate[].name array
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    //need to check input name vs name stored
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
            //when a matching name is found, match is increased and the number of their votes is increased. The
            //function stops
        }
    }
    //checks input name with all candidate names, if there's a match, match variable becomes nonzero, avoiding
    //a false output.
    return false;
    //ACTUALLY if no matches found then automatically stop
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //Need a number that will be set to the total, and then compared through the array. if the next number
    //is bigger then set as that number, else stay the same. once scanned, biggies number is stored. Now
    //scan through again, if number == votes then print name.
    int high = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (high < candidates[i].votes)
        {
            high = candidates[i].votes;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (high == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}