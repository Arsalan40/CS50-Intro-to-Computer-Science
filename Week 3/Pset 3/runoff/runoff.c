#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
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

// Numbers of voters and candidates
int voter_count;
int candidate_count;

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
//it will compare voters choice with candidate name if same, preference will be updated.

bool vote(int voter, int rank, string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)              //iterated through candidate count
    {
        if (strcmp(name, candidates[i].name) == 0)         //check if both names are same
        {
            preferences[voter][rank] = i;                 //if same set voters rank preference and return true
            return true;
        }
    }

    return false;                                      //if not found then false is returned
}

// Tabulate votes for non-eliminated candidates
//for this we have to update the total vote of candidate who is not eliminated

void tabulate(void)
{
    // TODO
    for (int i = 0; i < voter_count; i++)               //iterated through voter_count and candidate_count
    {
         for (int j = 0; j < candidate_count; j++)
         {
             int index = preferences[i][j];                  //store the preference in index
             if (candidates[index].eliminated == false)         //checking if preference is eliminated, if not then increment the votes
             {
                 candidates[index].votes++;
                 break;
             }
         }
    }

        return;
}

// Print the winner of the election, if there is one
//will print if there is any winner. votes must be more than half

bool print_winner(void)
{
    // TODO
    for (int i = 0; i < voter_count; i++)               //iterate through voter_count
    {
        if (candidates[i].votes > voter_count / 2)       //checking if candidate votes are greater then half of the votes
        {
            printf("%s\n", candidates[i].name);        //print name of candidate as winner
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
//this will check if anyone with min votes are still in election, which have to be eliminated

int find_min(void)
{
    // TODO
    int minimum_votes = MAX_VOTERS;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes < minimum_votes)   //checking if candidate has been eliminated and less then the max voters
        {
            minimum_votes = candidates[i].votes;
        }
    }
        return minimum_votes;
}

// Return true if the election is tied between all candidates, false otherwise
//this function is to check if election ended as a tie or not.

bool is_tie(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes != min)
        {
            return false;

        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
//this will eliminates the last person in the election
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}