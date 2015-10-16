#include <stdio.h>
#include <stdlib.h>
#include "qdbmp.h"
#include "binarytree.h"
#include <math.h>

Dictionary *LeerHeader(const char *path,int *width,int *height)
{
  int i;
  int size;
  int seplenght;
  Dictonary *dict;
  File *file;
  File=fopen(path, "rb");
  unsigned char leido;
  for(i=0; i<4; i++)
  {
    leido=fgetc(File);
    *width=*width+pow(256,i)*((int) leido);

  }
  for(i=0; i<4; i++)
  {
    leido=fgetc(File);
    *height=*height+pow(256,i)*((int) leido);

  }
  for(i=0; i<3; i++)
  {
    leido=fgetc(File);
    size=size+pow(256,i)*((int) leido);

  }
  dict = init_dictionary(size);
  for(i=0; i<3; i++)
  {
    leido=fgetc(File);
    seplength=seplength+pow(256,i)*((int) leido);

  }
}
