/*
    File:   minHeap.c
    Desc:   Program showing various operations on a binary min heap
    Author: Robin Thomas <robinthomas2591@gmail.com>
*/

#include <string.h>
#include "minheap.h"

#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2

minHeap initMinHeap(int size) {
    minHeap hp ;
    hp.size = 0 ;
    return hp ;
}

void swap(node *n1, node *n2) {
    node temp = *n1 ;
    *n1 = *n2 ;
    *n2 = temp ;
}

void heapify(minHeap *hp, int i) {
    int smallest = (LCHILD(i) < hp->size && hp->elem[LCHILD(i)].repetitions < hp->elem[i].repetitions) ? LCHILD(i) : i ;
    if(RCHILD(i) < hp->size && hp->elem[RCHILD(i)].repetitions < hp->elem[smallest].repetitions) {
        smallest = RCHILD(i) ;
    }
    if(smallest != i) {
        swap(&(hp->elem[i]), &(hp->elem[smallest])) ;
        heapify(hp, smallest) ;
    }
}

void buildMinHeap(minHeap *hp, LinkedList *pixeles) {
    int i ;
    Element *findeado;
    for(i = 0; i < pixeles->size; i++) {
        if(hp->size) {
            hp->elem = realloc(hp->elem, (hp->size + 1) * sizeof(node)) ;
        } else {
            hp->elem = malloc(sizeof(node)*pixeles->size) ;
        }
        node nd ;
        findeado = list_get(pixeles,i);
        nd.repetitions = findeado->repetitions;
        nd.r = findeado->r;
        nd.g = findeado->g;
        nd.b = findeado->b;
        nd.right = NULL;
        nd.left = NULL;
        hp->elem[(hp->size)++] = nd ;

    }
    for(i = (hp->size - 1) / 2; i >= 0; i--) {
        heapify(hp, i) ;
    }
}

void insertNode(minHeap *hp, node *data) {
    if(hp->size) {
        hp->elem = realloc(hp->elem, (hp->size + 1) * sizeof(node)) ;
    } else {
        hp->elem = malloc(sizeof(node)) ;
    }
    node *nd = malloc(sizeof(node));
    nd->repetitions = data->repetitions;
    nd->r = data->r;
    nd->g = data->g;
    nd->b = data->b;
    nd->right = data->right;
    nd->left = data->left;
    int i = (hp->size)++ ;
    while(i && nd->	repetitions < hp->elem[PARENT(i)].repetitions) {
        hp->elem[i] = hp->elem[PARENT(i)] ;
        i = PARENT(i) ;
    }
    memcpy(&hp->elem[i], nd, sizeof(node));
    free(nd);
}

void deleteNode(minHeap *hp,node *min) {
    if(hp->size) {
    	node *nd=malloc(sizeof(node));
    	nd->repetitions = hp->elem[0].repetitions;
    	nd->r = hp->elem[0].r;
    	nd->g = hp->elem[0].g;
    	nd->b = hp->elem[0].b;
    	nd->right = hp->elem[0].right;
    	nd->left = hp->elem[0].left;
    	memcpy(min, nd, sizeof(node));
    	free(nd);
        hp->elem[0] = hp->elem[--(hp->size)] ;
        hp->elem = realloc(hp->elem, hp->size * sizeof(node)) ;
        heapify(hp, 0) ;
    } else {
        printf("\nMin Heap is empty!\n") ;
        free(hp->elem);
    }
}

void deltree(node * tree)
{
    if (tree->right && tree->left)
    {
        deltree(tree->left);
        deltree(tree->right);
        free(tree->right);
        free(tree->left);
    }
}
void deleteMinHeap(minHeap *hp) {
    free(hp->elem) ;
}

void inorderTraversal(minHeap *hp, int i) {
    if(LCHILD(i) < hp->size) {
        inorderTraversal(hp, LCHILD(i)) ;
    }
    if(RCHILD(i) < hp->size) {
        inorderTraversal(hp, RCHILD(i)) ;
    }
}
void print_heap(minHeap *hp)
{
    int i;
    for (i=0;i<hp->size;i++)
    {
        printf("%i\n",hp->elem[i].repetitions);
    }
}
