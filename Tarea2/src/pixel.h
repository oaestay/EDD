#include "qdbmp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Pixel {
    int color;
    char *value;
}Pixel;

void pixel_test(Pixel *p);
Pixel *init_pixel();
void assign_pixel(Pixel *p, int i, char *path);
void destroy_pixel(Pixel *p);
void print_pixel(Pixel *p);
void int_to_rgb(int color, UCHAR *b, UCHAR *g, UCHAR *r);
int rgb_to_int(UCHAR r, UCHAR g, UCHAR b);
