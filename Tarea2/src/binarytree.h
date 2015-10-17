//##############################################################################
//
//                                  Tarea 2
//
//                       Oscar Estay   -   Bastian Mavrakis
//
//##############################################################################

#include "minheap.h"
#include "dictionary.h"

node *merge(node *arbol1,node *arbol2);

node initNode(int size);

node *Createtree(minHeap *heap);

void print_preorder(node *tree);

void print_inorder(node *tree);

void print_postorder(node *tree);

node* search(node **tree, int val);

void savePath(Dictionary *dict, node *tree, char *code);
