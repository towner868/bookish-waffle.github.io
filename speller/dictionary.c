// Implements a dictionary's functionality
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>


#include "dictionary.h"

typedef uint8_t  BYTE;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1431;

// Hash table
node *table[N];

//Total dictionary word size
long int wordCount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *cursor = table[hash(word)];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int wordAscii = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        wordAscii += tolower(word[i]);
    }
    return wordAscii % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];

    FILE *inptr = fopen(dictionary, "r");
    if (dictionary == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    while (fscanf(inptr, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);
        n->next = table[hash(word)];
        table[hash(word)] = n;
        wordCount++;
    }
    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (wordCount == 0)
    {
        return 0;
    }
    return wordCount;
}
// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    //free up memory
    int i = 0;
    node *cursor = 0;

    for (i = N - 1; i >= 0; i--)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }

    }
    if (i == 0 || cursor == NULL)
    {
        return true;
    }
    return false;
}