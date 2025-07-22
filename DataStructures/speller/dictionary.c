// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 8123; // Caguei na ordem alfabetica e fiz infinitas caixas. Aloca mais
                             // memória, o programa fica mais fast, não percorre tantos apontadores, percorre mais caixas
unsigned int actual_n_words = 0;
// Hash table
node *table[N];
//************************************************************************ */
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Obtem o índice da tabela hash para a palavra fornecida
    unsigned int index = hash(word);

    // Dar summon no apontador para percorrer as colisões ou os nós
    node *select = table[index];

    // Criar uma cópia da palavra em letras minúsculas para comparar

    // Agora percorrer o index dentro da tabela
    while (select != NULL)
    {
        // Palavra no node (dicionario) com a fornecida à função vinda do texto
        if (strcasecmp(select->word, word) == 0)
        {
            return true;
        }
        select = select->next; // Passar para o próximo nó
    }

    // Se a palavra não foi encontrada em nenhum nó da lista
    return false;
}

//************************************************************************ */
// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash_value = 0;

    for (int i = 0; word[i] != '\0'; i++) // Pato disse que as
    {
        hash_value = (hash_value * 23 + tolower(word[i])) %
                     N; // Abandonei os valores ordenados alfabeticamente. Assim crio mais slots na
                        // lista e ordeno ocasionalmente para aumentar o speed. Conta para separar em diferentes caixas 
    }

    return hash_value;
}

//************************************************************************* */

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL; // fazer reset a todas as posições da tabela para remover trash values
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));

        if (new_node == NULL)
        {
            printf("ERROR MEMORY ACCESSMENT\n");
            return false;
        }
        // meter em minusculas
        for (int i = 0, n = strlen(word); i < n; i++)
        {
            word[i] = tolower(word[i]);
        }
        strcpy(new_node->word, word);
        new_node->next = NULL; // RESET do endereço do próximo NODE para NULL

        // TODO - Ir buscar o indice da palavra para acrescentar ao. Função HASH ao que parece
        // unsigned int index =
        unsigned int index = hash(word);

        // Juntar o nó à lista, ou seja ao último anexado à lista de uma determinada letra
        new_node->next = table[index]; // Index esse Que vem de cima. O next aponta para a lista
        table[index] =
            new_node; // Para não remover o apontador que estava diretamente da lista para o último
        actual_n_words++;
    }
    fclose(file);
    return true;
}
//**************************************************************************** */
// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return actual_n_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *select = table[i];
        while (select != NULL)
        {
            node *temp = select;
            select = select->next;
            free(temp);
        }
    }
    return true;
}
