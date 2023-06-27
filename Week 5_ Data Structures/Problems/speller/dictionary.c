// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
// Buckets: One digit (0 and 9) for each letter, up to 4 digits (0 - 9999)
const unsigned int N = 9999;
// Max number of digits in hash table index is 4
#define HASH_DIGITS 4

// Hash table
node *table[N];

// Dictionary file and count
FILE *dictionaryFile = NULL;
int wordCount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashIndex = hash(word);

    for (node *tmp = table[hashIndex]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hashValue = 0;
    int hashLength = (strlen(word) > HASH_DIGITS) ? HASH_DIGITS : strlen(word);

    for (int i = 0; i < hashLength; i++)
    {
        hashValue += (toupper(word[i]) % 10) * pow(10, i);
    }
    return hashValue;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    dictionaryFile = fopen(dictionary, "r");
    if (dictionaryFile == NULL)
    {
        return false;
    }

    // Read strings from file one at a time
    char word[LENGTH + 1];
    while (fscanf(dictionaryFile, "%s", word) != EOF)
    {
        // Create two temp nodes; new = new node, tmp = copy of table
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Hash word to obtain a hash value
        int hashIndex = hash(word);

        // Copy word into node
        strcpy(n->word, word);
        wordCount++;

        // Insert node into hash table
        n->next = table[hashIndex];
        table[hashIndex] = n;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (dictionaryFile == NULL)
    {
        return 0;
    }
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Closes Dictionary & Checks for Close
    if (fclose(dictionaryFile) == 0)
    {
        for (int i = 0; i < N; i++)
        {
            node *n = table[i];

            while (n != NULL)
            {
                node *tmp = n->next;
                free(n);
                n = tmp;
            }

            if (n == NULL && i == N - 1)
            {
                return true;
            }
        }
    }
    return false;
}