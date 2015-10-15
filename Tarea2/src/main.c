//##############################################################################
//
//                                  Tarea 2
//
//                       Oscar Estay   -   Bastian Mavrakis
//
//##############################################################################

#include <stdio.h>
#include "linkedlist.h"
#include "binarytree.h"

int main(int argc, char const *argv[]) {

    BMP*    bmp;
    UCHAR  r, g, b;
    UINT    width, height;
    UINT    x, y;
    minHeap heap;
    node arbolito;

    LinkedList *list = list_init();

    bmp = BMP_ReadFile("Medio.bmp");
    BMP_CHECK_ERROR( stderr, -1 );

    width = BMP_GetWidth( bmp );
    height = BMP_GetHeight( bmp );
    printf("Width: %lu Height:%lu\n",width,height);

    for ( x = 0 ; x < width ; ++x )
    {
        for ( y = 0 ; y < height ; ++y )
        {
            BMP_GetPixelRGB( bmp, x, y, &r, &g, &b );
            list_add(list, r, g, b);
        }
    }
    heap = initMinHeap(list->size);
    buildMinHeap(&heap, list);
    inorderTraversal(&heap, 0);
    arbolito=*Createtree(&heap);
    list_print(list);
    printf("-----\n");
    char *str = "";
    Dictionary *d = init_dictionary(list->size);
    savePath(d ,&arbolito, str);
    print_dictionary(d);
    destroy_dictionary(d);
    deltree(&arbolito);
    BMP_Free(bmp);
    list_destroy(list);
    deleteMinHeap(&heap);

    return 0;
}
