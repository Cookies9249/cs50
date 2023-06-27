#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;

    // pointer to the next node
    // node *n - n is an address of a node
    struct node *next;
}
// node == pointer to a number and next node location
node;

int main(void)
{
    // List of unknown size
    node *list = NULL;

    // Make tmp node with set size
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }

    n->number = 1;      // go to address set in n, access int number, set to 1
    n->next = NULL;     // initialize next to 0
    // ALTERNATIVE: (*n).number = 1;

    // Copies address in n to list (list & n are both pointers)
    list = n;

    // Add number to list
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list);
        return 1;
    }

    n->number = 2;      // number is set to 2
    n->next = NULL;     // initialize next to 0
    list->next = n;     // address of next list is set to address of n;

    // Add number to list
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list->next);
        free(list);
        return 1;
    }

    n->number = 3;
    n->next = NULL;
    list->next->next = n;

    // Insert a value
    /*node *a = malloc(sizeof(node));
    node *b = malloc(sizeof(node));
    b->number = 9;
    b->next = NULL;
    a = list;

    for (int i = 0; i + 2 < 2; i++, a = a->next);
    b->next = a->next;
    a->next = b;*/

    // Print out List

    // Create a tmp node set to list
    // Every loop, set tmp to the next node
    // Repeat until there is no numbers left
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }

    // Free memory
    while (list != NULL)
    {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }

}