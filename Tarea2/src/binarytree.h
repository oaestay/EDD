#include <stdlib.h>
#include <stdio.h>

typedef struct node {
  int repetitions;
  UCHAR r;
  UCHAR g;
  UCHAR b;
  struct node * right, * left;
}node;


void insert(node ** tree, int val);


void print_preorder(node * tree);


void print_inorder(node * tree);


void print_postorder(node * tree);


void deltree(node * tree);


node* search(node ** tree, int val);
