#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

//preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

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

bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle_check(int i);


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

    //Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    int ranks[candidate_count];

    for (int i = 0; i < voter_count; i++)
    {
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
        printf("\n");
        record_preferences(ranks);
    }
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}
//The ranks index is the rank with the candidate's index as the data
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}
//If candidate is ranked lower (higher), their i over the respective j is incremented
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}
//If a set of coordinates is greater than its opposite, its i is the winner
void add_pairs(void)
{
    int k = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[k].winner = i;
                pairs[k].loser = j;
                k++;
                pair_count++;
            }
        }
    }
    return;
}
//The subtracting the winner's coordinates from its opposite yields the margin of victory
void sort_pairs(void)
{
    int k = 0;
    int margin[pair_count];
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                margin[k] = preferences[i][j] - preferences[j][i];
                k++;
            }
        }
    }
    //This syncs up two arrays, margin and pairs
    pair sorted;
    for (int i = 1; i <= pair_count - 1; i++)
    {
        if (margin[i] > margin[i - 1])
        {
            sorted = pairs[i];
            pairs[i] = pairs[i - 1];
            pairs[i - 1] = sorted;
        }
    }
    return;
}
//Understanding that the winner of i can't be the loser of j of an already locked pair
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        if (cycle_check(i) == true)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
}
//Needed to zero out the i counter so that the beginning of each column resets
void print_winner(void)
{
    for (int j = 0; j < candidate_count; j++)
    {
        int counter = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] == false)
            {
                counter++;
            }
            if (counter == candidate_count)
            {
                printf("%s\n", candidates[j]);
            }
        }
    }
}
//Checks to see if a the pair has already been locked, and if new edge would create cycle
bool cycle_check(int i)
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[pairs[i].loser][pairs[j].winner])
        {
            if (pairs[j].loser == pairs[i].winner || pairs[j + 1].loser == pairs[i].winner)
            {
                return true;
            }
        }
    }
    return false;
}