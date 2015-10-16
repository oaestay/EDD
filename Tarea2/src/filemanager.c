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
    char *sep = malloc(w + 1);
    strcpy(sep, d->sep);
    int counter = 0;
    char buffer = '\0';
    int color;
    for (int i = 0; i < w; i++) {
        if (counter == 7){
            if(sep[i] == '1'){
                buffer += 1;
            }
            fwrite(&buffer, sizeof(char), 1, ptr_myfile);
            counter = 0;
            buffer = '\0';
        }
        if(sep[i] == '0')
        {
            buffer = buffer << 1;
            counter += 1;
        }
        else{
            buffer += 1;
            buffer = buffer << 1;
            counter += 1;
        }
    }
    for (int i = 0; i < d->size; i++) {
        color = d->pixels[i]->color;
        b =  color & 255;
        g =  (color >> 8) & 255;
        r =  (color >> 16) & 255;
        buffer = buffer << (7 - counter);
        buffer += (r >> counter);
        fwrite(&buffer, sizeof(char), 1, ptr_myfile);
        buffer = '\0';
        buffer += (r << (8 - counter));
        buffer += (g >> counter);
        fwrite(&buffer, sizeof(char), 1, ptr_myfile);
        buffer = '\0';
        buffer += (g << (8 - counter));
        buffer += (b >> counter);
        fwrite(&buffer, sizeof(char), 1, ptr_myfile);
        buffer = '\0';
        buffer += (b << (8 - counter));
        buffer = buffer >> (7 - counter);
        for (int j = 0; j < strlen(d->pixels[i]->value); j++) {
            if (counter == 7){
                if(d->pixels[i]->value[j] == '1'){
                    buffer += 1;
                }
                fwrite(&buffer, sizeof(char), 1, ptr_myfile);
                counter = 0;
                buffer = '\0';
            }
            if(d->pixels[i]->value[j] == '0')
            {
                buffer = buffer << 1;
                counter += 1;
            }
            else{
                buffer += 1;
                buffer = buffer << 1;
                counter += 1;
            }
        }
        for (int i = 0; i < w; i++) {
            if (counter == 7){
                if(sep[i] == '1'){
                    buffer += 1;
                }
                fwrite(&buffer, sizeof(char), 1, ptr_myfile);
                counter = 0;
                buffer = '\0';
            }
            if(sep[i] == '0')
            {
                buffer = buffer << 1;
                counter += 1;
            }
            else{
                buffer += 1;
                buffer = buffer << 1;
                counter += 1;
            }
        }
    }
    if (counter > 0){
        fwrite(&buffer, sizeof(char), 1, ptr_myfile);
    }
    fclose(ptr_myfile);
    free(sep);
    //Destroy everything
    destroy_dictionary(d);
    deltree(&arbolito);
    BMP_Free(bmp);
    list_destroy(list);
    deleteMinHeap(&heap);

    return 0;
};
