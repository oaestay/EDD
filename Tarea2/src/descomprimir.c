#include <stdio.h>
#include <stdlib.h>
#include "qdbmp.h"
#include "binarytree.h"
// @param bit = 0 - 7
int get_bit(unsigned char c, int n)
{
    return (c & (1 << (n-1))) != 0;
}
void Codification(char *palabra, char *delimiter, char *returneado)
{
  char *sepi = strstr(palabra,delimiter);

  for (int i=0;i<strlen(palabra);i++)
  {
    if (sepi != &(palabra[i]))
    {
      returneado[i] = palabra[i];
    }
  }
  return;
}
unsigned char Stringuchar(char *color)
{
  unsigned char temp;
  unsigned char acumulado;
  for(int i=0;i<8;i++)
  {
    if (color[i]=='1')
    {
      temp = 1 << 0;
      acumulado = acumulado | temp;
    }
    acumulado = acumulado << 1;
  }
  return acumulado;
}
void LeerHeader(const char *path,int *width,int *height)
{
  int i;
  int size;
  int filesize;
  int seplength;
  int j;
  int k;
  UCHAR r;
  UCHAR g;
  UCHAR b;
  char red [9];
  char green [9];
  char blue [9];

  unsigned char leido;
  Dictionary *dict;
  FILE *file;
  file=fopen(path, "rb");
  fseek(file, 0, SEEK_END); // seek to end of file
  filesize = ftell(file); // get current file pointer
  fseek(file, 0, SEEK_SET);
  char concatenacion [(filesize-14)*8+1];
  char *codificacion=malloc((filesize-14)*8+1*sizeof(char));
  unsigned char bytes [14];

  for(i=0;i<filesize;i++)
  {

      if (i<14)
      {
        bytes[i]=fgetc(file);
      }
      else
      {
        leido = fgetc(file);
        for (j=0;j<8;j++)
        {
          if (get_bit(leido,8-j))
          {
            concatenacion[(i-14)*8+j] = '1';
          }
          else
          {
            concatenacion[(i-14)*8+j] = '0';
          }
        }
      }
  }
  concatenacion[(filesize-14)*8]='/0';

  *width = (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | (bytes[3]);
  *height = (bytes[4] << 24) | (bytes[5] << 16) | (bytes[6] << 8) | (bytes[7]);
  size = (bytes[8] << 16) | (bytes[9] << 8) | (bytes[10] );
  seplength = (bytes[11] << 16) | (bytes[12] << 8) | (bytes[13]);
  char separador[seplength+1];
  char concatenacion1[(filesize-14)*8+1-seplength];
  char concatenaciontemp[(filesize-14)*8+1-seplength];
  memcpy( separador, &concatenacion[0], seplength);
  memcpy( concatenacion1, &concatenacion[seplength], (filesize-14)*8+1-seplength);
  separador[seplength] = '\0';
  dict = init_dictionary(size+1);






  int w=0;
  int v=0;
  int contador=0;
  int t=0;
  for (k=0;k<size;k++)
  {

    memcpy(red, &concatenacion1[0+w], 8);
    red[8]='\0';
    memcpy(green, &concatenacion1[8+w], 8);
    green[8]='\0';
    memcpy(blue, &concatenacion1[16+w], 8);
    blue[8]='\0';
    w = w +24;
    //printf("%d\n",w);
    r = (UCHAR)Stringuchar(red);
    g = (UCHAR)Stringuchar(green);
    b = (UCHAR)Stringuchar(blue);

    for (i = w;i< strlen(concatenacion1);i++)
    {
        for (v=0;v<seplength;v++)
        {
            //printf("%d\n",i);
            if (concatenacion1[v+i] != separador[v])
		{
                  contador = 0;
                  break;
		}
            else
		{
	          contador = contador+1;
		}
        }
        if (contador == seplength)
	{
           //printf("%d\n",contador);
           contador = 0 ;
           codificacion = realloc(codificacion,(i-w)*sizeof(char));
	   for (t=w;t<i;t++)
	   {

               codificacion[t-w] = concatenacion1 [t];
           }
	   break;
	}
    }
    codificacion[t-w]='\0';

    w = v+i;

    printf("%s\n",codificacion);


    insert_dictionary(dict, r, g, b, 6, codificacion);



  }



  //*height = *bytes[4]+*bytes[5]*256+*bytes[6]*256*256+*bytes[7]*256*256*256;
  //size = *bytes[8]+*bytes[9]*256+*bytes[10]*256*256;

  //seplength = *bytes[11]+*bytes[12]*256+*bytes[13]*256*256;

  printf("%d\n",*width);
  printf("%d\n",*height);
  printf("%d\n",size);
  printf("%d\n",seplength);
  printf("%s\n",separador);
  //printf("%s\n",concatenacion1);
  fclose(file);
  for(i = w ; i<strlen(concatenacion1); i++)
  {

  }
  free(codificacion);

}
