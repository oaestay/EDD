#include <stdio.h>
#include <stdlib.h>
#include "qdbmp.h"
#include "binarytree.h"
// @param bit = 0 - 7
int get_bit(unsigned char c, int n)
{
    return (c >> n) & 1;
}
Dictionary *LeerHeader(const char *path,int *width,int *height)
{
  int i;
  int size;
  int filesize;
  int seplength;
  Dictionary *dict;
  FILE *file;
  file=fopen(path, "rb");
  fseek(file, 0, SEEK_END); // seek to end of file
  filesize = ftell(file); // get current file pointer
  fseek(file, 0, SEEK_SET);
  unsigned char bytes [filesize];
  unsigned char ints [4];
  for(i=0;i<filesize;i++)
  {
      bytes[i]=fgetc(file);
    }

  }
  bytes[0]=ints[0];
  bytes[1]=ints[1];
  bytes[2]=ints[2];
  bytes[3]=ints[3];
  *width = *(int *)ints;

  //*height = *bytes[4]+*bytes[5]*256+*bytes[6]*256*256+*bytes[7]*256*256*256;
  //size = *bytes[8]+*bytes[9]*256+*bytes[10]*256*256;
  //dict = init_dictionary(size);
  //seplength = *bytes[11]+*bytes[12]*256+*bytes[13]*256*256;

  printf("%d\n",*width);
  //printf("%d\n",*height);
  //printf("%d\n",size);
  //printf("%d\n",seplength);
  fclose(file);
  return dict;

}
