#include "qdbmp.h"
#include <string.h>

typedef struct Pixel {
    int color;
    char *value;
}Pixel;

typedef struct Dictionary {
    Pixel *pixels;
    int size;
}Dictionary;

void dictionary_alloc_test(Dictionary *d);
Dictionary *init_dictionary(int size);
void insert_dictionary(Dictionary *d, UCHAR r, UCHAR g, UCHAR b, char *path);
void destroy_dictionary(Dictionary *d);
void print_dictionary(Dictionary *d);

int rgb_to_int(UCHAR r, UCHAR g, UCHAR b);

int hash(int color, int size, int try);
