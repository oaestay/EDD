#include <stdlib.h>
#include <stdio.h>
#include "binarytree.h"


node *merge(node *arbol1,node *arbol2)
{
  node * newroot = (node *)malloc(sizeof(node));
  newroot->repetitions = arbol1->repetitions + arbol2->repetitions;
  newroot->left = arbol1;
  newroot->right = arbol2;
}

void print_preorder(node * tree)
{
    if (tree)
    {
        printf("%d\n",tree->repetitions);
        print_preorder(tree->left);
        print_preorder(tree->right);
    }

}

void print_inorder(node * tree)
{
    if (tree)
    {
        print_inorder(tree->left);
        printf("%d\n",tree->repetitions);
        print_inorder(tree->right);
    }
}

void print_postorder(node * tree)
{
    if (tree)
    {
        print_postorder(tree->left);
        print_postorder(tree->right);
        printf("%d\n",tree->repetitions);
    }
}

void deltree(node * tree)
{
    if (tree)
    {
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }
}

node* search(node ** tree, int val)
{
    if(!(*tree))
    {
        return NULL;
    }

    if(val < (*tree)->data)
    {
        search(&((*tree)->left), val);
    }
    else if(val > (*tree)->repetitions)
    {
        search(&((*tree)->right), val);
    }
    else if(val == (*tree)->repetitions)
    {
        return *tree;
    }
}
