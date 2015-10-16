#include "filemanager.h"

int Compress_BMP(char *input, char *output){
    BMP* bmp;
    UCHAR r, g, b;
    UINT width, height;
    UINT x, y;
    minHeap heap;
    node arbolito;

    //Open BMP file, read the width and weight
    bmp = BMP_ReadFile(input);
    BMP_CHECK_ERROR(stderr, -1);
    width = BMP_GetWidth( bmp );
    height = BMP_GetHeight( bmp );

    //Initialize of the List of colors
    LinkedList *list = list_init();

    //Getting the pixels of the image
    for ( x = 0 ; x < width ; ++x )
    {
        for ( y = 0 ; y < height ; ++y )
        {
            BMP_GetPixelRGB( bmp, x, y, &r, &g, &b );
            list_add(list, r, g, b, 0);
        }
    }
    list_add(list,0,0,0,1);

    //Building the heap to order the list
    heap = initMinHeap(list->size);
    buildMinHeap(&heap, list);
    inorderTraversal(&heap, 0);

    //Building the Huffmann tree
    arbolito=*Createtree(&heap);

    //Creating the dictionary
    Dictionary *d = init_dictionary(list->size);

    //Recursively saving the paths with the colors in the dictionary
    savePath(d ,&arbolito, "");

    print_dictionary(d);
    //Destroy everything
    destroy_dictionary(d);
    deltree(&arbolito);
    BMP_Free(bmp);
    list_destroy(list);
    deleteMinHeap(&heap);

    return 0;
};
