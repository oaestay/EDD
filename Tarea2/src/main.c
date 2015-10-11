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

    bmp = BMP_ReadFile("colores.bmp");
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
    list_print(list);
    heap = initMinHeap(list->size);
    buildMinHeap(&heap, list);
    inorderTraversal(&heap, 0);

    arbolito=*Createtree(&heap);


    savePath(&arbolito, 0);

    deltree(&arbolito);
    BMP_Free(bmp);
    list_destroy(list);
    deleteMinHeap(&heap);

    return 0;
}
