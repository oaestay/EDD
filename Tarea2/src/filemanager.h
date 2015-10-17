//##############################################################################
//
//                                  Tarea 2
//
//                       Oscar Estay   -   Bastian Mavrakis
//
//##############################################################################

#include "binarytree.h"

int Compress_BMP(char *input, char *output);
void Write_binary(char *output, Dictionary *d, BMP *bmp);
void LeerHeader(const char *path,int *width,int *height);
int get_bit(unsigned char c, int n);
unsigned char Stringuchar(char *color);
