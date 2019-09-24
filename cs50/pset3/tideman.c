/*

The Tideman voting method (also known as “ranked pairs”) is a ranked-choice voting method
that’s guaranteed to produce the Condorcet winner of the election if one exists.
*/

/*
To handle this, the Tideman algorithm must be careful to avoid creating cycles in the candidate graph.
How does it do this? The algorithm locks in the strongest edges first, since those are arguably the most
significant. In particular, the Tideman algorithm specifies that matchup edges should be “locked in” to
the graph one at a time, based on the “strength” of the victory (the more people who prefer a candidate
over their opponent, the stronger the victory). So long as the edge can be locked into the graph without
creating a cycle, the edge is added; otherwise, the edge is ignored.


*/
#include <cs50.h>
#include <stdio.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
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
    // Checking inputs
    if (name == NULL || strlen(name) == 0 || rank < 0 || rank > MAX)
    {
        return false;
    }

    // where i is the index in the array and j is the next voters rank
    int i = 0, j = 0;

    for (int i = 0, j = 0; i < candidate_count; i++ )
    {
        if (!(strcmp(candidates[i], name) == 0))
        {
            continue;
        }

        ranks[i] = j;
        j++;
    }

    // Should i make a test to confirm that ranks is not filled w/ empty values?


    // The vote function in this case should return true to indicate a successful ballot.
    return true;
    }

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

