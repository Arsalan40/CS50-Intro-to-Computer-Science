#include <cs50.h>
#include <stdio.h>
#include <string.h>



//Statement: Program will take sequence of votes as input and output winner of election

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
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }


    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
//it will looks for the candidate matching the users choice, if found it will update the vote count of that candidate

bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)              // iterating through the candidate count
    {
        if (strcmp(name, candidates[i].name) == 0)                   //checking if both names are same
        {
            candidates[i].votes++;                                 //every time name is equal to candidate name there vote is incremented by 1
            return true;
        }
    }
    return false;

}

// Print the winner (or winners) of the election
// in this we have to print candidate name with most vote,
//if both candidate have same votes print both names

void print_winner(void)
{
    int total_Votes = 0;
// TODO
    for (int i = 0; i < candidate_count; i++)                                   //here from 0-count checking if each candidate vote is less than 0, change total vote with the candidate votes
    {
        if (candidates[i].votes > total_Votes  )
         {
            total_Votes = candidates[i].votes;
        }
        }

    for (int j = 0; j < candidate_count; j++)
    {
       if (candidates[j].votes == total_Votes)                                //if each candidate vote is equal to total_votes print the name of candidate
      {
           printf("%s\n", candidates[j].name);
      }
    }
}