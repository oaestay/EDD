#include "pixel.h"

typedef struct Dictionary {
    int size;
    Pixel **pixels;
    int len_sep;
    char *sep;
}Dictionary;

void dictionary_alloc_test(Dictionary *d);
Dictionary *init_dictionary(int size);
void insert_dictionary(Dictionary *d, UCHAR r, UCHAR g, UCHAR b, int repetitions, char *path);
char *get_dictionary(Dictionary *d, UCHAR r, UCHAR g, UCHAR b);
void destroy_dictionary(Dictionary *d);
void print_dictionary(Dictionary *d);

int hash(int color, int size, int try);
