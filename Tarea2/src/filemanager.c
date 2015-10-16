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

    //Writting the binary file
	FILE *ptr_myfile;
    ptr_myfile = fopen(output,"wb");
    if (!ptr_myfile){
        printf("Unable to open file!");
        return 1;
    }
    int w = width;
    char p[4];
    p[3] = w & 255;
    p[2] = (w >> 8) & 255;
    p[1] = (w >> 16) & 255;
    p[0] = (w >> 24) & 255;
    fwrite(p, sizeof(char), 4, ptr_myfile);
    w = height;
    p[3] = w & 255;
    p[2] = (w >> 8) & 255;
    p[1] = (w >> 16) & 255;
    p[0] = (w >> 24) & 255;
    fwrite(p, sizeof(char), 4, ptr_myfile);
    w = list->size - 1;
    p[2] = w & 255;
    p[1] = (w >> 8) & 255;
    p[0] = (w >> 16) & 255;
    fwrite(p, sizeof(char), 3, ptr_myfile);
    w = d->len_sep;
    p[2] = w & 255;
    p[1] = (w >> 8) & 255;
    p[0] = (w >> 16) & 255;
    fwrite(p, sizeof(char), 3, ptr_myfile);
    int counter = 0;
    char buffer = '\0';
    for (int i = w - 1; i >= 0 ; i--) {
        /* code */
    }
    p[2] = w & 255;
    p[1] = (w >> 8) & 255;
    p[0] = (w >> 16) & 255;
    fwrite(p, sizeof(char), 3, ptr_myfile);

    fclose(ptr_myfile);

    //Destroy everything
    destroy_dictionary(d);
    deltree(&arbolito);
    BMP_Free(bmp);
    list_destroy(list);
    deleteMinHeap(&heap);

    return 0;
};
