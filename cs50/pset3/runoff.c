#include <cs50.h>
#include <stdio.h>

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

/*
You may assume that no two candidates will have the same name.
Hints
Recall that candidate_count stores the number of candidates in the election.
Recall that you can use strcmp to compare two strings.
Recall that preferences[i][j] stores the index of the candidate who is the jth ranked preference for the ith voter.
*/
// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Checking inputs
    if (name == NULL || strlen(name) == 0)
    {
        return false;
    }

    if ( voter < 0 || voter > MAX_VOTERS || rank < 0 || rank > MAX_CANDIDATES)
    {
        return  false;
    }

    for (int i = 0; i < candidate_count; i++) 
    { 
        // Should my program record to see if that 
        if (strcmp(candidates[i].name, name) == 0 )
        {
            // Recall that preferences[i][j] stores the index of the candidate who is the jth ranked preference for the ith voter.
            preferences[voter][rank] = i;

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
/*

their top choice candidate is represented by preferences[i][0],
their second choice candidate by preferences[i][1], etc.
Recall that the candidate struct has a field called eliminated,
which will be true if the candidate has been eliminated from the election.
Recall that the candidate struct has a field called votes,
which you’ll likely want to update for each voter’s preferred candidate.
*/
// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    for (int i = 0; i < voter_count; i++)
    {
        int j = 0;
        while (j  < candidate_count) //update the candidate_count - to enhcance the code
        {
            if (!candidates[preferences[i][j]].eliminated)
            {
                continue;
            }
            
            candidates[preferences[i][j]].votes += (candidate_count-j);
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    if( candidate_count == 0) return false;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count/2)
        {
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    if (voter_count == 0 || candidate_count == 0)
    {
        return 0;
    }

    int i = 0, min = voter_count;

    while (i < candidate_count) //update the candidate_count - to enhance the code
    {
        if (candidates[i].eliminated)
        {
            continue;
        }

        if (candidates[i].votes < min){
            min = candidates[i].votes
        }

    }

    return min;
}
/*
The function should return true if every candidate remaining in the election has the same number of votes, and should return false otherwise.
Hints
Recall that a tie happens if every candidate still in the election has the same number of votes. Note, too, that the is_tie function takes an
argument min, which is the smallest number of votes any candidate currently has. How might you use that information to determine if the election
is a tie (or, conversely, not a tie)?
*/
// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int i = 0;
    while (i  < candidate_count) //update the candidate_count - to enhance the code
    {
        if (candidates[i].eliminated)
        {
            continue;
        }

        if (candidates[i].votes != min){
            return false;
        }

    }

    return true;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    int i = 0;
    while (i  < candidate_count) //update the candidate_count - to enhance the code
    {
        if (candidates[i].eliminated)
        {
            continue;
        }

        if (candidates[i].votes <= min){
            candidates[i].eliminated = true;
        }

    }
    return;
}
