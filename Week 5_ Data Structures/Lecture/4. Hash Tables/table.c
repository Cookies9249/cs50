#include <stdio.h>
#include <stdlib.h>

// Tries are linked links of hash tables
// - Each entry on a hash table leads to another hash table
#define SIZE_OF_ALPHABET 26
#define LONGEST_WORD 50

// Hash Functions
typedef struct hash
{
    char word[LONGEST_WORD + 1];
    struct hash *next;
}
hash;

// Tries
typedef struct tries
{
    bool is_word;
    struct tries *children[SIZE_OF_ALPHABET];
}
tries;

// Queues: (FIFO) First In, First Out - eg. Lineups
// Stacks: (LIFO) Last In, First Out - eg. Stack of Trays