// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Words Loaded
unsigned int loadedwords;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    // Make pointer to go through linked list
    node *cursor = table[hash(word)];

    // While there is a word to read
    while (cursor != NULL)
    {
        // Return true if match
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            // Move to next word in linked list
            cursor = cursor->next;
        }
    }
    // When NULL is reached no words remain
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    // Set hash table pointers to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");

    // Make sure it opens properly
    if (dict == NULL)
    {
        printf("Could not open dictionary/n");
        return false;
    }

    // Make buffer to store word and node
    char *dword = malloc((LENGTH + 1) * sizeof(char));
    node *tmp;

    // Prep to count loaded words
    loadedwords = 0;

    // Read and store dictionary words in dword
    while (fscanf(dict, "%s", dword) != EOF)
    {
        tmp = malloc(sizeof(node));
        if (tmp == NULL)
        {
            return false;
        }

        // Store dictionary word in tmp
        strcpy(tmp->word,dword);

        // Point tmp at first node in linked list
        tmp->next = table[hash(dword)];

        //point table at tmp
        table[hash(dword)] = tmp;

        // increment loaded word count
        loadedwords++;
    }

    // Tidying up
    free (dword);
    fclose(dict); // Why does this give an error? // Allocated too small a number of chars for dword (N when should have done LENGTH + 1). This gummed things up when more memory was loaded in than was available
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return loadedwords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor = NULL;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];

        while(cursor != NULL)
        {
            cursor = table[i]->next;
            free(table[i]);
            table[i] = cursor;
        }
    }
    return true;
}


