/*
Name: David Bruno
Date: 09/24/2019
File: plurality.c
*/

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

// Winning Vote Count
int winningCount;

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

    // Initialize teh winning count to 0
    winningCount = 0;

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


bool vote(string name)
{
    if (name == NULL || strlen(name) == 0)
    {
        return false;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0 )
        {
            // Update vote totals given a new vote
            candidates[i].votes++;

            // Keeps track of the current maxVotes
            if (candidates[i].votes > winningCount)
            {
                winningCount++;
            }

            // The vote function in this case should return true to indicate a successful ballot.
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election // Do the winners have to be printed in alphabetical order?
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == winningCount)
        {
            printf("%s\n",candidates[i].name);
        }
    }
    return;
}

