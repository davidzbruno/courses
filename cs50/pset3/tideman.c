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
    for (int i = 0; i < candidate_count-1; i++)
    {
        preference[ranks[i]][ranks[i+1]]++;
        // printf("Candidate #%d is %d votes ahead of Candidate #%d", ranks[i], preference[ranks[i]][ranks[i+1]], ranks[i+1]);
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0, j = 0; i < candidate_count-1; i++)
    {
        int votesA = preferences[i][i+1];
        int votesB = preferences[i+1][i];;
        pair temp;

        if(votesA == votesB)
        {
            continue;
        }
        else if(votesA > votesB)
        {
            temp.winner = votesA;
            temp.loser = votesB;
        }
        else
        {
            temp.winner = votesB;
            temp.loser = votesA;
        }

        pair[j] = temp;
        // printf("pair added");
        pair_count++;
    }

    return;
}

/*
The function should sort the pairs array in decreasing order of strength of victory, where strength of victory is defined to be the
number of voters who prefer the preferred candidate. If multiple pairs have the same strength of victory, you may assume that the order does not matter.
Complete the lock_pairs function.
The function should create the locked graph, adding all edges in decreasing order of victory strength so long as the edge would not create a cycle.
Complete the print_winner function.
The function should print out the name of the candidate who is the source of the graph. You may assume there will not be more than one source.
*/

// Sort pairs in decreasing order by strength of victory
// implementing a merge sort alogrithm
void sort_pairs(void)
{
    // for every pair of candidates where one candidate is ahead
    for (int i = 0; i < pair_count; i++)
    {
        pairs[i].winner
    }

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

