#include "pixel.h"

void pixel_test(Pixel *p){
    if (p == NULL)
    {
        exit(EXIT_FAILURE);
    }
};

Pixel *init_pixel(){
    Pixel *p = malloc(sizeof(*p));
    pixel_test(p);
    p->color = 0;
    p->value = "";
    return p;
};

void assign_pixel(Pixel *p, int i, char *path){
    pixel_test(p);
    p->color = i;
    p->value = malloc(strlen(path) + 1);
    strcpy(p->value, path);
};

void destroy_pixel(Pixel *p){
    pixel_test(p);
    free(p->value);
    free(p);
};

void print_pixel(Pixel *p){
    //int_to_RGB
    UCHAR b =  p->color & 255;
    UCHAR g =  (p->color >> 8) & 255;
    UCHAR r =  (p->color >> 16) & 255;
    printf("r: %x g: %x b: %x -> %s\n", r, g, b, p->value);
};

int rgb_to_int(UCHAR r, UCHAR g, UCHAR b){
    int sum = 0;
    sum += r;
    sum = sum << 8;
    sum += g;
    sum = sum << 8;
    sum += b;
    return sum;
};