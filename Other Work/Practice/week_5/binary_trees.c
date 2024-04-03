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

void free_memory(node *root);

int main(void)
{
    // Tree of size 0
    node *tree = NULL;

    // Add number to tree
    node *n = malloc(sizeof(node));

    if (n == NULL)
    {
        return 1;
    }

    n->number = 2;
    n->left = NULL;
    n->right = NULL;
    tree = n;

    // At this point we have a box with the number 2 in it and 2 empty pointers

    // Add another number
    n = malloc(sizeof(node));

    if (n == NULL)
    {
        free(tree);
        return 1;
    }

    n->number = 1;
    n->left = NULL;
    n->right = NULL;
    tree->left = n;

    // Now we have a second box down and to the left of the first with the number 1 in it.
    // Add another box
    n = malloc(sizeof(node));

    if (n == NULL)
    {
        free(tree->left);
        free(tree);
        return 1;
    }

    n->number = 3;
    n->left = NULL;
    n->right = NULL;
    tree->right = n;

    // We now have a parrent box with #2 and two children left and right with #1 and #3 respectively.
    print_tree(tree);
    free_memory(tree);

}


// Recursive print function
void print_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    print_tree(root->left);
    printf("%i\n",root->number);
    print_tree(root->right);
}

// Recursive free function, be sure to free the current block AFTER freeing the children
void free_memory(node *root)
{
    if (root == NULL)
    {
        return;
    }
    free_memory(root->left);
    free_memory(root->right);
    free(root);
}