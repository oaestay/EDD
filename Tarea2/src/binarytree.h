#include <stdlib.h>
#include <stdio.h>
#include "qdbmp.h"
#include "minheap.h"

node *merge(node *arbol1,node *arbol2);

node initNode(int size);

node *Createtree(minHeap *heap);

void print_preorder(node *tree);

void print_inorder(node *tree);

void print_postorder(node *tree);

node* search(node **tree, int val);

void savePath(node *tree, int Code);
