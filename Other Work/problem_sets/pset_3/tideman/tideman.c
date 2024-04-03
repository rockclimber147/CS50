#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
// unlike runoff, int going in preferences isn't indexed to candidate, i and j are indexed to two candidates
// and the int stored is the number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;
//if more people prefer i over j than j over i, i is winner etc.
//need to think about ties.

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
        //candidates[0] is first candidate, and so on
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    //need to compare input name vs list of names to make sure vote is valid
    //increase validity by 1 if input name matches one of the candidates
    int validity = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            validity++;
            ranks[rank] = i;
        }
    }
    //matching one candidate increases validity by 1, so anything other than 1 should give false result
    if (validity != 1)
    {
        return false;
    }
    //need to update ranks[] with voter input rank and corresponding candidate
    //ranks[] is recorded for each voter i
    //just added line to validity check, sets ranks[rank] to i since i is the candidate's index and
    //when name of rank is candidate[i] then that's the candidate to record.
    return true;
}

// Update preferences given one voter's ranks
//int preferences [i][j] is number of voters who prefer i over j
//ranks[] is calculated for voter i then used to fill preferences, then reset for voter i + 1.
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
            //ranks stores indexed candidates, so update preferences for first ranked candidate avove the remainder
            //then second ranked above remainder and so on, this will repear for all voters and populate preferences
            //with all candate combinations and the number of times they appear
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //pairs[i] contains for each i a winner and a loser, both being integers indexed to a candidate
    //preferences shows how many times a candidate is preferred over another
    //for i to be a winner over j, prferences[i][j] > preferences[j][i]
    //margin of victory of i over j is the difference of those preferences (might use this more when sorting
    //Added the global integer pair_count
    //Definitely needed that to get check50 to be happy. I suppose what I did before worked but
    //it didn't store the pair count in the correct place
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if ((preferences[i][j] > preferences[j][i]) && i != j)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    //need to consider all combinations of candidates and populate pairs once per winner in all cases
    //ignore when comparing candidates against themselves and losing against winning candidates as the winners
    //will be recorded
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //Pairs now have a winner and a loser, and the margin ov victory which we want to sort for
    //MOV is preferences[winner][loser] - preferences[l][w]
    //there are pair_count pairs
    for (int i = 0; i < pair_count; i++)
    {
        int high = 0;
        //set high to be the largest win/loss margin
        for (int j = i; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner] > high)
            {
                high = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            }
            //once high is found, find the pair that corresponds with that value of high
            //swap that pair with the one infirst place
            //every pairs[i] will have a winner and loser associated with i
            //how to swap two parts of an array without deleting one?
            //would have to overwrite pairs[0] with highest margin pair
            //need placeholder pair in array to store destination pair then when p[0] is overwritten
            //copy placeholder pair values to original
            //change p to start at 1 instead of 0 and use 0 as placeholder
        }
        for (int j = i; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner] == high)
            {
                //Store i in 0.
                pairs[pair_count + 1] = pairs[i];
                //store max in i.
                pairs[i] = pairs[j];
                //store 0 (now i) in j.
                pairs[j] = pairs[pair_count + 1];
                //increment i in case there's a tie for the current margin so both get counted
                i++;
            }
        }
        //had to make transient place at the end instead of in position 0 to make check50 happy

    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
//bool locked[i][j] means i is locked over j
//a cycle would be if a line were to meet its starting point
//because of how the margins are calculated, can't have a 2 cycle
//lock in edges one at a time based on strength (pairs should be already sorted by strength)
//lock[pairs[i].winner][pairs[i].loser] is bool, so true/false, good for print_winner
//once locked in, compare loser to any previously locked winners,

//Once a pair is locked then that should be it, so check first then lock.
//condition for not being locked is forming a loop. Since we are locking pairs in order of
//decreasing edge, if the current pair being locked would form a loop then it would be the one to skip.
//How to check?
//First pair locks automatically as no way a loop can be formed.
//second pair should check identity of winner vs identity of loser of most recently locked pair.
//If it's a match, check associated locked winner against second most recently locked loser.
//continue until either no more locked losers available or the winner locked with the loser is the loser
//of the pair that is being checked, indicating a loop and setting the status of false for locked

{
    for (int i = 0; i < pair_count; i++)
    {
        //follow int stores the identity of the winning candidate as it moves along the list
        int follow = pairs[i].winner;
        //check stores the identity of the losing candidate of the current pair
        //set locked to true, then unset if a loop is found
        locked[pairs[i].winner][pairs[i].loser] = true;
        //count backwards from pairs[i] to compare against
        for (int j = 0; j < pair_count; j++)
        {
            for (int k = 0; k < pair_count; k++)
            {
                if ((follow == pairs[k].loser) && (locked[pairs[k].winner][pairs[k].loser] == true))
                {
                    follow = pairs[k].winner;
                }
                if (follow == pairs[i].loser)
                {
                    locked[pairs[i].winner][pairs[i].loser] = false;
                }
            }
        }
    }
    return;
    //had to make a third iteration with k to account for the cases where pairs had to be checked in reverse order
}

// Print the winner of the election
void print_winner(void)

//Need to search through all locked pairs and see if the winner is a loser on any other pair
//If yes, then search if that winner is a loser elsewhere, and so on. If it doesn't match any losers then they
//are the source of the graph.

{
    //need to figure out tied winners, but also assume there isn't more than one source
    int win = 0;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (locked[pairs[j].winner][pairs[j].loser] == true && win == pairs[j].loser)
            {
                win = pairs[j].winner;
            }
        }
    }
    printf("%s\n", candidates[win]);
    return;
}