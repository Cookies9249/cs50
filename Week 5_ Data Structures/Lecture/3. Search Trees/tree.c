#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
}
node;

void print_tree(node *root);
void free_tree(node *root);
bool search(node *root, int number);

int main(void)
{
    node *tree = NULL;

    // Add 1st Number
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }

    n->number = 2;
    n->left = NULL;
    n->right = NULL;
    tree = n;

    // Add 2nd Number
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }

    n->number = 1;
    n->left = NULL;
    n->right = NULL;
    tree->left = n;

    // Add 3rd Number
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }

    n->number = 3;
    n->left = NULL;
    n->right = NULL;
    tree->right = n;

    print_tree(tree);

    int search_number = get_int("Search for: ");
    if (search(tree, search_number))
    {
        printf("In Tree\n");
    }
    else
    {
        printf("Not In Tree\n");
    }

    free_tree(tree);
}

void print_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    print_tree(root->left);
    printf("%i\n", root->number);
    print_tree(root->right);
}

void free_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

/*bool search(node *root, int number)
{
    if (root == NULL)
    {
        return false;
    }
    else if (number < root->number)
    {
        return(search(root->left, number));
    }
    else if (number > root->number)
    {
        return(search(root->right, number));
    }
    else
    {
        return true;
    }
}*/


bool search(node *root, int number)
{
    if (root != NULL)
    {
        if (search(root->left, number) || search(root->right, number) || root->number == number)
        {
            return true;
        }
    }
    return false;
}