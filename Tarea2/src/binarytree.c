#include <stdlib.h>
#include <stdio.h>
#include "binarytree.h"

node initNode(int size) {
    node nd ;
    nd.repetitions = 0 ;
    return nd ;
}

node *merge(node *arbol1,node *arbol2)
{
  node * newroot = (node *)malloc(sizeof(node));
  newroot->repetitions = arbol1->repetitions + arbol2->repetitions;
  newroot->left = arbol1;
  newroot->right = arbol2;
  return newroot;
}

node Createtree(minHeap *heap)
{
  node menor1;
  node menor2;
  node temproot;
  int i = heap->size-1;
  while(i > 0 )
  {
    deleteNode(heap,&menor1);
    deleteNode(heap,&menor2);
    &temproot=merge(&menor1,&menor2);
    i--;
  }
  return temproot;

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

    if(val < (*tree)->repetitions)
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
    return NULL;
}
