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

};






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
Dictionary *d = init_dictionary(list->size);
savePath(d ,&arbolito, "");
print_dictionary(d);
BMP_GetPixelRGB(bmp, 50, 30, &r, &g, &b);
printf("r: %x g: %x b: %x \n", r, g, b);
printf("%s\n", get_dictionary( d, r, g, b));
destroy_dictionary(d);
deltree(&arbolito);
BMP_Free(bmp);
list_destroy(list);
deleteMinHeap(&heap);
