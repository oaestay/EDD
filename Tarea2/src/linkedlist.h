/******************************************************************************\
|
|   Author:     Chaumier Pierre-Victor <pvchaumier@uc.cl>
|
\******************************************************************************/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include "qdbmp.h"

typedef struct Element
{
    int repetitions;
    UCHAR r;
    UCHAR g;
    UCHAR b;
    struct Element *next;
    struct Element *previous;
}Element;

typedef struct LinkedList
{
    Element *first;
    Element *last;
    int size;
}LinkedList;

LinkedList *list_init();
void list_alloc_test(LinkedList *list);
void list_destroy(LinkedList *linkedlist);
void list_add(LinkedList *linkedlist, UCHAR r, UCHAR g, UCHAR b, int sep);
void list_del(LinkedList *linkedlist, UCHAR r, UCHAR g, UCHAR b);
Element *list_get(LinkedList *linkedlist, int iPosition);
void list_print(LinkedList *linkedlist);

#endif
