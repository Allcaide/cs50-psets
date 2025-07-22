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
} pair;

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

    // Query for votes (vai passar pelos diferentes boletins de votos)
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
    // TODO
    // Check if name is valid
    // if name valid update rank with ith rank
    // if name invalid return false
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) ==
            0) // Pára o for para o i do candidato para registar o rank, pois a ranks não fica
               // preenchida com nomes de candidatos, mas sim com a anexação i com a ordem com a
               // qual meteram os nomes

        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO record de number of voters that preferes the candidate i over the candidate j
    for (int i = 0; i < candidate_count; i++) // percorrer por ordem o rank
    {
        for (int j = i + 1; j < candidate_count;
             j++) // percorrer os seguintes para registar no preferences
        {
            int prefered_candidate = ranks[i];
            int least_prefered = ranks[j];

            preferences[prefered_candidate]
                       [least_prefered]++; // That preferes i over i+1 on hte ranks array. and
                                           // increment the amount of voters who have that
                                           // preference
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++) // Percorrer os candidatos
    {
        for (int j = i + 1; j < candidate_count;
             j++) // Percorrer os seguintes para verificar quem prefere quem
        {
            if (preferences[i][j] <
                preferences[j][i]) // Se o candidato j é preferido ao candidato i
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            else if (preferences[i][j] >
                     preferences[j][i]) // Se o candidato i é preferido ao candidato j
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++) /// Ver este deve faltar -i
        {
            int vote1 = preferences[pairs[j].winner][pairs[j].loser];
            int vote2 = preferences[pairs[j + 1].winner][pairs[j + 1].loser];

            if (vote1 < vote2)
            {
                pair temporary = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temporary;
            }
        }
    }
    return;
}

bool makes_cycle(int winner, int loser)
{
    if (winner == loser) // Se o perdedor for o mesmo que o vencedor da disputa, há ciclo. Acabou
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++) // percorre os cadidatos para ver se o perdedor está
                                              // locked com algum, se tiver fecha ciclo
    {
        if (locked[loser][i]) // Se já tiver locked, ou locker[][]=true?
        {
            if (makes_cycle(winner,
                            i)) // Rerns até encontrar o par a->b b->c c->a? Se simS true. Se
                                // não encontrar esgota a iteração pelos candidatos e devolve false
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count;
         i++) // Percorrer a função pairs por ordem decrescente de maior importância
    {
        int winner = pairs[i].winner; // Associar a variáveis para dar lock nos pares
        int loser = pairs[i].loser;

        if (!makes_cycle(winner,
                         loser)) // Aidna falta Construir função para verificar se fecha o ciclo.
        {
            locked[winner][loser] = true; // Se não existir ciclo, da lock na combinação
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                is_winner = false;
                break;
            }
        }
        if (is_winner)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
