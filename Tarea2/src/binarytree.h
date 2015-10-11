#include <stdlib.h>
#include <stdio.h>
#include "qdbmp.h"
typedef struct node {
  int repetitions;
  UCHAR r;
  UCHAR g;
  UCHAR b;
  struct node *right, *left;
}node;

node *merge(node *arbol1,node *arbol2);


void print_preorder(node * tree);


void print_inorder(node * tree);


void print_postorder(node * tree);


void deltree(node * tree);


node* search(node ** tree, int val);
