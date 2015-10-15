#include "dictionary.h"
#include <stdlib.h>

Dictionary *init_dictionary(int size){
    Dictionary *dictionary = malloc(sizeof(dictionary));
    dictionary_alloc_test(dictionary);
    dictionary->pixels = malloc(sizeof(Pixel)*size);
    dictionary->size = size;
    for (int i = 0; i < size; i++) {
        dictionary->pixels[i].color = 0;
        dictionary->pixels[i].value = malloc(sizeof(char));
        *(dictionary->pixels[i].value) = '\0';
    }
    return(dictionary);
};

void dictionary_alloc_test(Dictionary *d){
    if (d == NULL)
    {
        exit(EXIT_FAILURE);
    }
};

void insert_dictionary(Dictionary *d, UCHAR r, UCHAR g, UCHAR b, char *path)
{
    dictionary_alloc_test(d);
    int i = rgb_to_int(r, g, b);
    int alloc = 0;
    int try = 0;
    while (alloc == 0){
        int index = hash(i, d->size, try);
        if(*(d->pixels[index].value) == '\0')
        {
            alloc = 1;
            d->pixels[index].value = malloc(strlen(path) + 1);
            strcpy(d->pixels[index].value, path);
        }
        else{
            try += 1;
        }
    }
};

void destroy_dictionary(Dictionary *d){
    dictionary_alloc_test(d);
    for (int i = 0; i < d->size; i++) {
        free(d->pixels[i].value);
    }
    free(d->pixels);
    free(d);
};

void print_dictionary(Dictionary *d){
    dictionary_alloc_test(d);
    for (int i = 0; i < d->size; i++) {
        printf("%d -> %s\n", d->pixels[i].color, d->pixels[i].value);
    }
}

int rgb_to_int(UCHAR r, UCHAR g, UCHAR b){
    int sum = 0;
    sum += r;
    sum = sum << 8;
    sum += g;
    sum = sum << 8;
    sum += b;
    return sum;
};

int hash(int color, int size, int try){
    return (color + try)%size;
};
