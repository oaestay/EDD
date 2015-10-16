#include "dictionary.h"

Dictionary *init_dictionary(int size){
    Dictionary *dictionary = malloc(sizeof(*dictionary));
    dictionary_alloc_test(dictionary);
    dictionary->size = size - 1;
    dictionary->pixels = malloc(sizeof(Pixel*) * dictionary->size);
    for (int i = 0; i < size - 1; i++) {
        dictionary->pixels[i] = init_pixel();
    }
    dictionary->len_sep = 0;
    dictionary->sep = "";
    return(dictionary);
};

void dictionary_alloc_test(Dictionary *d){
    if (d == NULL)
    {
        exit(EXIT_FAILURE);
    }
};

void insert_dictionary(Dictionary *d, UCHAR r, UCHAR g, UCHAR b, int repetitions, char *path)
{
    dictionary_alloc_test(d);
    if (repetitions == 0){
        d->sep = malloc(strlen(path) + 1);
        strcpy(d->sep, path);
        d->len_sep = strlen(path);
    }
    else{
        int i = rgb_to_int(r, g, b);
        int alloc = 0;
        int try = 0;
        while (alloc == 0){
            int index = hash(i, d->size, try);
            if(!strcmp(d->pixels[index]->value, ""))
            {
                alloc = 1;
                assign_pixel(d->pixels[index], i, path);
            }
            else{
                try += 1;
            }
        }
    }
};

char *get_dictionary(Dictionary *d, UCHAR r, UCHAR g, UCHAR b)
{
    dictionary_alloc_test(d);
    int i = rgb_to_int(r, g, b);
    int alloc = 0;
    int try = 0;
    while (alloc == 0){
        int index = hash(i, d->size, try);
        if(i == d->pixels[index]->color)
        {
            alloc = 1;
            return(d->pixels[index]->value);
        }
        else{
            try += 1;
        }
    }
    return("");
};

void destroy_dictionary(Dictionary *d){
    dictionary_alloc_test(d);
    for (int i = 0; i < d->size; i++) {
        destroy_pixel(d->pixels[i]);
    }
    free(d->pixels);
    free(d->sep);
    free(d);
};

void print_dictionary(Dictionary *d){
    dictionary_alloc_test(d);
    for (int i = 0; i < d->size; i++) {
        print_pixel(d->pixels[i]);
    }
}

int hash(int color, int size, int try){
    return (color + try)%size;
};
