#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "binarytree.h"
#include <string.h>

node initNode(int size) {
    node nd ;
    nd.repetitions = 0 ;
    return nd ;
}

node *merge(node *arbol1,node *arbol2)
{
  node *newroot = malloc(sizeof(node));
  newroot->r = '\0';
  newroot->g = '\0';
  newroot->b = '\0';
  newroot->left = malloc(sizeof(node));
  newroot->right = malloc(sizeof(node));
  newroot->repetitions = arbol1->repetitions + arbol2->repetitions;
  memcpy((newroot->left),arbol1,sizeof(node));
  memcpy((newroot->right),arbol2,sizeof(node));
  //newroot->left = arbol1;
  //newroot->right = arbol2;

  return newroot;
}

node *Createtree(minHeap *heap)
{
  node menor1;
  node menor2;
  node *temproot;
  int i = heap->size-1;
  while(i > 0 )
  {
    deleteNode(heap,&menor1);
    deleteNode(heap,&menor2);
    temproot=merge(&menor1,&menor2);
    insertNode(heap,temproot);
    i--;
    free(temproot);

  }


  return &heap->elem[0];


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
        printf("%d huehue\n",tree->repetitions);
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
void savePath(node *tree, int Code){
    if (tree->r != '\0')
        //codeTable[(int)tree->letter] = Code;
        printf("%d %d %d -> %i \n", tree->r, tree->g, tree->b, Code);
    else{
        savePath(tree->left, Code*10+1);
        savePath(tree->right, Code*10+2);
    }

    return;
}
