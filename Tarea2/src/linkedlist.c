#include "linkedlist.h"

void list_alloc_test(LinkedList *list){
    if (list == NULL)
    {
        exit(EXIT_FAILURE);
    }
}

LinkedList *list_init()
{
    LinkedList *list = malloc(sizeof(*list));
    Element *element = malloc(sizeof(*element));

    if (list == NULL || element == NULL)
    {
        exit(EXIT_FAILURE);
    }

    element->repetitions = 0;
    element->r = 0;
    element->g = 0;
    element->b = 0;
    element->next = NULL;
    element->previous = NULL;

    list->first = element;
    list->last = element;
    list->size = 0;

    return list;
}

void list_destroy(LinkedList *list)
{
    list_alloc_test(list);

    Element *elementCurrent, *elementNext;

    elementCurrent = list->first;
    while (elementCurrent != NULL)
    {
        elementNext = elementCurrent->next;
        free(elementCurrent);
        elementCurrent = elementNext;
    }
    free(elementCurrent);
    free(elementNext);
    free(list);
}

void list_add(LinkedList *list, UCHAR r, UCHAR g, UCHAR b)
{
    list_alloc_test(list);

    Element *elementCurrent, *elementPrevious;

    if (list->size == 0)
    {
        list->first->r = r;
        list->first->g = g;
        list->first->b = b;
        list->first->repetitions = 1;
        list->size += 1;
    }
    else if (list->size == 1)
    {
        elementCurrent = list->first;
        if (elementCurrent->r == r && elementCurrent->g == g && elementCurrent->b == b)
        {
            elementCurrent->repetitions += 1;
        }
        else
        {
            Element *element = malloc(sizeof(*element));
            if (element == NULL)
            {
                exit(EXIT_FAILURE);
            }
            element->r = r;
            element->g = g;
            element->b = b;
            element->repetitions = 1;
            element->next = NULL;
            element->previous = list->last;

            list->last->next = element;
            list->last = element;
            list->size += 1;
        }
    }
    else
    {
        elementPrevious = list->first;
        elementCurrent = elementPrevious->next;

        if (elementPrevious->r == r && elementPrevious->g == g && elementPrevious->b == b)
        {
            elementPrevious->repetitions += 1;
        }
        else
        {
            int iKeepGoing = 1;
            while (elementCurrent != NULL && iKeepGoing == 1)
            {
                if (elementCurrent->r == r && elementCurrent->g == g && elementCurrent->b == b)
                {
                    iKeepGoing = 0;
                    elementCurrent->repetitions += 1;
                }
                else
                {
                    elementPrevious = elementCurrent;
                    elementCurrent = elementCurrent->next;
                }
            }
            if (iKeepGoing == 1)
            {
                Element *element = malloc(sizeof(*element));
                if (element == NULL)
                {
                    exit(EXIT_FAILURE);
                }
                element->r = r;
                element->g = g;
                element->b = b;
                element->repetitions = 1;
                element->next = NULL;
                element->previous = list->last;

                list->last->next = element;
                list->last = element;
                list->size += 1;
            }
        }
    }
}

void list_del(LinkedList *list, UCHAR r, UCHAR g, UCHAR b)
{
    list_alloc_test(list);

    Element *elementCurrent, *elementPrevious;

    if (list->size == 0)
    {
        printf("ERROR. List is empty, nothing to delete\n");
    }
    else if (list->size == 1)
    {
        elementCurrent = list->first;
        if (elementCurrent->r == r && elementCurrent->g == g && elementCurrent->b == b)
        {
            free(elementCurrent);
            list->first = NULL;
            list->last = NULL;
            list->size = 0;
        }
        else
        {
            printf("ERROR. Element not in list, nothing to delete\n");
        }
    }
    else
    {
        elementPrevious = list->first;
        elementCurrent = elementPrevious->next;

        if (elementPrevious->r == r && elementPrevious->g == g && elementPrevious->b == b)
        {
            list->first = elementCurrent;
            elementCurrent->previous = NULL;
            list->size -= 1;
            free(elementPrevious);
        }
        else
        {
            int iKeepGoing = 1;
            while (elementCurrent != NULL && iKeepGoing == 1)
            {
                if (elementCurrent->r == r && elementCurrent->g == g && elementCurrent->b == b)
                {
                    iKeepGoing = 0;
                    elementPrevious->next = elementCurrent->next;
                    list->size -= 1;
                    if (elementCurrent->next == NULL)
                    {
                        list->last = elementPrevious;
                    }
                    else
                    {
                        elementCurrent->next->previous = elementPrevious;
                    }
                    free(elementCurrent);
                }
                else
                {
                    elementPrevious = elementCurrent;
                    elementCurrent = elementCurrent->next;
                }
            }
            if (iKeepGoing == 1)
            {
                printf("ERROR. Element not found.\n");
            }
        }
    }
}
Element *list_get(LinkedList *list, int iPosition)
{
    list_alloc_test(list);

    Element *elementCurrent;

    if (iPosition > list->size - 1)
    {
        printf("ERROR. The list only contains %d elements.\n", list->size);
        return NULL;
    }
    else
    {
        int i;
        elementCurrent = list->first;
        for (i = 0; i < iPosition; i++)
        {
            elementCurrent = elementCurrent->next;
        }
        return elementCurrent;
    }
}


void list_print(LinkedList *list)
{
    list_alloc_test(list);

    Element *elementCurrent;

    printf("{");

    if (list->size > 0)
    {
        elementCurrent = list->first;
        while (elementCurrent != NULL)
        {
            printf("(r: %d g: %d b: %d, repetitions = %i)", elementCurrent->r, elementCurrent->g, elementCurrent->b, elementCurrent->repetitions);
            elementCurrent = elementCurrent->next;
            if (elementCurrent != NULL)
            {
                printf(", ");
            }
        }
    }
    printf("}\n");
}
