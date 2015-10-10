/*
    File:   minHeap.c
    Desc:   Program showing various operations on a binary min heap
    Author: Robin Thomas <robinthomas2591@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linkedlist.h"

#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2

typedef struct pixel {
    int repetitions;
    UCHAR r;
    UCHAR g;
    UCHAR b;
} pixel ;

typedef struct minHeap {
    int size ;
    pixel *elem ;
} minHeap ;


/*
    Function to initialize the min heap with size = 0
*/
minHeap initMinHeap(int size);

/*
    Function to swap data within two nodes of the min heap using pointers
*/
void swap(pixel *n1, pixel *n2);

/*
    Heapify function is used to make sure that the heap property is never violated
    In case of deletion of a node, or creating a min heap from an array, heap property
    may be violated. In such cases, heapify function can be called to make sure that
    heap property is never violated
*/
void heapify(minHeap *hp, int i);


/*
    Build a Min Heap given an array of numbers
    Instead of using insertNode() function n times for total complexity of O(nlogn),
    we can use the buildMinHeap() function to build the heap in O(n) time
*/
void buildMinHeap(minHeap *hp, LinkedList *pixeles) ;


//void buildMinHeap(minHeap *hp, LinkedList *arr, int size) {
  //  int i ;

    // Insertion into the heap without violating the shape property
    //for(i = 0; i < size; i++) {
      //  if(hp->size) {
        //    hp->elem = realloc(hp->elem, (hp->size + 1) * sizeof(pixel)) ;
        //} else {
          //  hp->elem = malloc(sizeof(pixel)) ;
      //  }
      //  node nd ;
      //  nd.data = arr[i] ;
      //  hp->elem[(hp->size)++] = nd ;
  //  }

    // Making sure that heap property is also satisfied
    //for(i = (hp->size - 1) / 2; i >= 0; i--) {
      //  heapify(hp, i) ;
    }
}


/*
    Function to insert a node into the min heap, by allocating space for that node in the
    heap and also making sure that the heap property and shape propety are never violated.
*/
void insertNode(minHeap *hp, Element data);

/*
    Function to delete a node from the min heap
    It shall remove the root node, and place the last node in its place
    and then call heapify function to make sure that the heap property
    is never violated
*/
void deleteNode(minHeap *hp,pixel *min) ;


/*
    Function to get maximum node from a min heap
    The maximum node shall always be one of the leaf nodes. So we shall recursively
    move through both left and right child, until we find their maximum nodes, and
    compare which is larger. It shall be done recursively until we get the maximum
    node
*/


/*
    Function to clear the memory allocated for the min heap
*/
void deleteMinHeap(minHeap *hp) ;

/*
    Function to display all the nodes in the min heap by doing a preorder traversal
*/



/*
    Function to display all the nodes in the min heap by doing a post order traversal
*/




}