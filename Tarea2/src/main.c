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

    /* Read an image file */
    bmp = BMP_ReadFile("test.bmp");
    BMP_CHECK_ERROR( stderr, -1 ); /* If an error has occurred, notify and exit */

    /* Get image's dimensions */
    width = BMP_GetWidth( bmp );
    height = BMP_GetHeight( bmp );
    printf("Width: %lu Height:%lu\n",width,height);

    /* Iterate through all the image's pixels */
    for ( x = 0 ; x < width ; ++x )
    {
        for ( y = 0 ; y < height ; ++y )
        {
            /* Get pixel's RGB values */
            BMP_GetPixelRGB( bmp, x, y, &r, &g, &b );
            /* Adding pixels to the list */
            list_add(list, r, g, b);
        }
    }
    list_print(list);
    heap = initMinHeap(list->size);
    buildMinHeap(&heap, list);
    inorderTraversal(&heap, 0);


    &arbolito = Createtree(&heap);
    deltree(&arbolito);
    BMP_Free(bmp);
    list_destroy(list);
    deleteMinHeap(&heap);

    return 0;
}
