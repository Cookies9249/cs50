#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
bool creates_cycle(int start, int check);
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

// Update ranks given a new vote (makes sure of valid vote)
// Repeats once every voter every rank input
bool vote(int rank, string name, int ranks[])
{
    // for each candidate i
    for (int i = 0; i < candidate_count; i++)
    {
        // if the vote matches candidate name
        if (strcmp(name, candidates[i]) == 0)
        {
            // rank is set to candidate number
            ranks[rank] = i;
            return true;
        }
    }
    // if vote matches no candidate, false if returned
    return false;
}

// Update preferences given one voter's ranks
// Repeats once every voter
void record_preferences(int ranks[])
{
    // for candidate rank i
    for (int i = 0; i < candidate_count; i++)
    {
        // for candidate rank j (rank j is every rank below rank i)
        // therefore candidate rank i is prefered over every candidate rank j
        for (int j = i + 1; j < candidate_count; j++)
        {
            // number of preferences of i over j is increased
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // for candidate i
    for (int i = 0; i < candidate_count; i++)
    {
        // for candidate j
        for (int j = 0; j < candidate_count; j++)
        {
            // if more people prefer i over j
            if (preferences[i][j] > preferences[j][i])
            {
                // pair winner and loser are up
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;

                // number of pairs is increased
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // repeats i times to perform bubble sort
    for (int i = 0; i < pair_count; i++)
    {
        // for each pair j
        for (int j = 0; j < pair_count; j++)
        {
            // if pair j + 1 victory is stronger than pair j victory
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                // pair j + 1 is brought to front
                pair tmp = pairs[j + 1];
                pairs[j + 1] = pairs[j];
                pairs[j] = tmp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // for each pair i
    for (int i = 0; i < pair_count; i++)
    {
        // calls creates_cycle function
        if (!creates_cycle(pairs[i].loser, pairs[i].winner))
        {
            // if a cycle is not discovered, the pair is locked in
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Checks if locking in a pair will create a cycle
// s = loser of source pair; original candidate; carries over function calls (stays the same)
// c = candidate being checked; set to winner of previously checked pair + checked for loss in another pair
bool creates_cycle(int s, int c)
{
    // if function returns to original candidate s
    if (s == c)
    {
        // there is a cycle and true is returned
        return true;
    }

    // for each candidate i
    for (int i = 0; i < candidate_count; i++)
    {
        // if candidate c lost to candidate i in a pair
        if (locked[i][c])
        {
            // calls itself with candidate i being checked
            // if a cycle is eventually discovered (creates_cycle = true), result is carried back to lock_pairs function
            return (creates_cycle(s, i));
        }
    }
    // returns false if no cycle is discovered
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // for candidate i
    for (int i = 0; i < candidate_count; i++)
    {
        // winner is temporarily set to true
        bool winner = true;

        // checked with every other candidate
        for (int j = 0; j < candidate_count; j++)
        {
            // if candidate i lost to any other candidate j
            if (locked[j][i])
            {
                // they cannot be a winner
                winner = false;
            }
        }

        // if winner is not set to false (candidate i is found to never lost a pair)
        if (winner)
        {
            // candidate i is determined as the winner
            printf("%s\n", candidates[i]);
        }
    }
}