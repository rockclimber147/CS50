#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
// i is the voter and j goes to the candidate the voter prefers. Need a variable as voter can have multiple
// different preferences, each assiggned an importance, j.
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];
//populates array called candidates with candidate struct, call on candidates array to get values.

// Numbers of voters and candidates
int voter_count;
int candidate_count;
//I guess declaring variables outside of main makes them global, so I can use them across all functions?

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }
    //Sets all values of candidates to default

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            //voter i gets asked who their rank 1 is, and they input a name. preferences is an int that can't
            //be a string, so preferences won't store the name of the candidate, just a number for that one voter and rank
            //need to index names to a number in preferences

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();
        //Need to look at top choice for voters, top choice being the lowest ranking candidate that hasn't been eliminated.
        //Where are the ranks for each candidate stored? Votes are already all cast and this loop doesn't include voting process
        //preferences for voter i and candidate j are stored as an integer, doesn't seem to accept name string, but this is what
        //is needed to call on with tabulate, and vote() takes voter#, rank#, and candidate name as inputs.
        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    int check = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        //all voters and all their ranks will be input here from separate loops
        //for each vote/rank combo, check the name string of the jth candidate against the one that was inputted.
        // if there's a match, that candidate number matches the name and will be stored in preferences for that voter/rank.
        if (strcmp(candidates[j].name, name) == 0)
        {
            preferences[voter][rank] = j;
            check++;
        }
    }
    if (check != 1)
        //if no matches are found check will be 0 and no valid name has been detected
    {
        return false;
    }
    return true;
}

// Tabulate votes for non-eliminated candidates
// Need to increment .votes of candidate by 1 for each time they are first choice
// first choice is preferences[i][0], i being voter and int stored by vote is candidates[i].name
void tabulate(void)
{
    //.votes already reset to 0
    //Need to count first votes and rank + 1 votes if rank is eliminated
    //repeat for each voter
    int eliminated_count = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].eliminated == true)
        {
            eliminated_count++;
        }
    }
    for (int i = 0; i < voter_count; i++)
    {
        int rank = 0;
        //need to determine appropriate rank to use before comparing preferences[i][rank] to j
        //scan every candidate in order vs top preference of i. scanning once isn't enough, scan for amount of eliminated candidates.
        //scan through everyone once for each eliminated person to ensure that rank is increased for any order the voter voted for.
        for (int e = 0; e < eliminated_count; e++)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                if (preferences[i][rank] == j && candidates[j].eliminated == true)
                {
                    rank++;
                }
            }
        }
        for (int j = 0; j < candidate_count; j++)
        {
            //Need to make sure that rank is increased by 1 every time the first choice or modified first choice lands on an
            //eliminated candidate
            //change choice of voter if their preferred candidate is eliminated. preferred candidate is first choice
            if (preferences[i][rank] == j && candidates[j].eliminated == false)
            {
                candidates[j].votes++;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
//Winner has more than 50% of the vote
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes > (voter_count / 2))
            //More than 50% means no tie is possible
        {
            printf("%s\n", candidates[j].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = 0;
    for (int i = 0; i < voter_count / candidate_count + 1; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (min == candidates[j].votes && candidates[j].eliminated == false)
            {
                return min;
            }
        }
        min++;
    }
    return 0;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int at_min = 0;
    int elim = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].eliminated == true)
        {
            elim++;
        }
        else if (candidates[j].votes == min)
        {
            at_min++;
        }
    }
    if (at_min + elim == candidate_count)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes == min)
        {
            candidates[j].eliminated = true;
        }
    }
    return;
}