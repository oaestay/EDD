#include "filemanager.h"

int Compress_BMP(char *input, char *output){
    BMP* bmp;
    UCHAR r, g, b;
    UINT width, height;
    UINT x, y;
    minHeap heap;
    node arbolito;

    //Open BMP file, read the width and weight
    bmp = BMP_ReadFile(input);
    BMP_CHECK_ERROR(stderr, -1);
    width = BMP_GetWidth( bmp );
    height = BMP_GetHeight( bmp );

    //Initialize of the List of colors
    LinkedList *list = list_init();

    //Getting the pixels of the image
    for ( x = 0 ; x < width ; ++x )
    {
        for ( y = 0 ; y < height ; ++y )
        {
            BMP_GetPixelRGB( bmp, x, y, &r, &g, &b );
            list_add(list, r, g, b, 0);
        }
    }
    list_add(list,0,0,0,1);

    //Building the heap to order the list
    heap = initMinHeap(list->size);
    buildMinHeap(&heap, list);
    inorderTraversal(&heap, 0);

    //Building the Huffmann tree
    arbolito=*Createtree(&heap);

    //Creating the dictionary
    Dictionary *d = init_dictionary(list->size);

    //Recursively saving the paths with the colors in the dictionary
    savePath(d ,&arbolito, "");

    //Writting the binary file
    Write_binary(output, d, bmp);

    //Destroy everything
    destroy_dictionary(d);
    deltree(&arbolito);
    BMP_Free(bmp);
    list_destroy(list);
    deleteMinHeap(&heap);

    return 0;
};

void Write_binary(char *output, Dictionary *d, BMP *bmp){
    FILE *ptr_myfile;
    UCHAR r, g, b;
    UCHAR _r, _g, _b;
    UINT x, y;
    char *path = "";
    ptr_myfile = fopen(output,"wb");
    if (!ptr_myfile){
        EXIT_FAILURE;
    }
    int wi = BMP_GetWidth(bmp);
    char p[4];
    p[3] = wi & 255;
    p[2] = (wi >> 8) & 255;
    p[1] = (wi >> 16) & 255;
    p[0] = (wi >> 24) & 255;
    fwrite(p, sizeof(char), 4, ptr_myfile);
    int he = BMP_GetHeight(bmp);
    p[3] = he & 255;
    p[2] = (he >> 8) & 255;
    p[1] = (he >> 16) & 255;
    p[0] = (he >> 24) & 255;
    fwrite(p, sizeof(char), 4, ptr_myfile);
    int w = d->size;
    p[2] = w & 255;
    p[1] = (w >> 8) & 255;
    p[0] = (w >> 16) & 255;
    fwrite(p, sizeof(char), 3, ptr_myfile);
    w = d->len_sep;
    p[2] = w & 255;
    p[1] = (w >> 8) & 255;
    p[0] = (w >> 16) & 255;
    fwrite(p, sizeof(char), 3, ptr_myfile);
    char *sep = malloc(w + 1);
    strcpy(sep, d->sep);
    int counter = 0;
    char buffer = '\0';
    int color;
    for (int i = 0; i < w; i++) {
        if (counter == 7){
            if(sep[i] == '1'){
                buffer += 1;
            }
            fwrite(&buffer, sizeof(char), 1, ptr_myfile);
            counter = 0;
            buffer = '\0';
        }
        else{
            if(sep[i] == '0')
            {
                buffer = buffer << 1;
                counter += 1;
            }
            else{
                buffer += 1;
                buffer = buffer << 1;
                counter += 1;
            }
        }
    }
    for (int i = 0; i < d->size; i++) {
        color = d->pixels[i]->color;
        b =  color & 255;
        g =  (color >> 8) & 255;
        r =  (color >> 16) & 255;
        buffer = buffer << (7 - counter);
        buffer += (r >> counter);
        fwrite(&buffer, sizeof(char), 1, ptr_myfile);
        buffer = '\0';
        buffer += (r << (8 - counter));
        buffer += (g >> counter);
        fwrite(&buffer, sizeof(char), 1, ptr_myfile);
        buffer = '\0';
        buffer += (g << (8 - counter));
        buffer += (b >> counter);
        fwrite(&buffer, sizeof(char), 1, ptr_myfile);
        buffer = '\0';
        buffer += (b << (8 - counter));
        buffer = buffer >> (7 - counter);
        for (int j = 0; j < strlen(d->pixels[i]->value); j++) {
            if (counter == 7){
                if(d->pixels[i]->value[j] == '1'){
                    buffer += 1;
                }
                fwrite(&buffer, sizeof(char), 1, ptr_myfile);
                counter = 0;
                buffer = '\0';
            }
            else{
                if(d->pixels[i]->value[j] == '0')
                {
                    buffer = buffer << 1;
                    counter += 1;
                }
                else{
                    buffer += 1;
                    buffer = buffer << 1;
                    counter += 1;
                }
            }
        }
        for (int i = 0; i < w; i++) {
            if (counter == 7){
                if(sep[i] == '1'){
                    buffer += 1;
                }
                fwrite(&buffer, sizeof(char), 1, ptr_myfile);
                counter = 0;
                buffer = '\0';
            }
            else{
                if(sep[i] == '0')
                {
                    buffer = buffer << 1;
                    counter += 1;
                }
                else{
                    buffer += 1;
                    buffer = buffer << 1;
                    counter += 1;
                }
            }
        }
    }
    _r = 0;
    _g = 0;
    _b = 0;
    for ( x = 0 ; x < wi ; ++x )
    {
        for ( y = 0 ; y < he ; ++y )
        {
            BMP_GetPixelRGB( bmp, x, y, &r, &g, &b );
            if (r != _r && g != _g && b != _b){
                path = get_dictionary(d, r, g, b);
                _r = r; _g = g; _b = b;
            }
            for (int j = 0; j < strlen(path); j++) {
                if (counter == 7){
                    if(path[j] == '1'){
                        buffer += 1;
                    }
                    fwrite(&buffer, sizeof(char), 1, ptr_myfile);
                    counter = 0;
                    buffer = '\0';
                }
                else{
                    if(path[j] == '0')
                    {
                        buffer = buffer << 1;
                        counter += 1;
                    }
                    else{
                        buffer += 1;
                        buffer = buffer << 1;
                        counter += 1;
                    }
                }
            }
        }
    }
    if (counter > 0){
        buffer = buffer << (7 - counter);
        fwrite(&buffer, sizeof(char), 1, ptr_myfile);
    }
    fclose(ptr_myfile);
    free(sep);
}
int get_bit(unsigned char c, int n)
{
    return (c & (1 << (n-1))) != 0;
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




    insert_dictionary(dict, r, g, b, 6, codificacion);



  }



  //*height = *bytes[4]+*bytes[5]*256+*bytes[6]*256*256+*bytes[7]*256*256*256;
  //size = *bytes[8]+*bytes[9]*256+*bytes[10]*256*256;

  //seplength = *bytes[11]+*bytes[12]*256+*bytes[13]*256*256;


  //printf("%s\n",concatenacion1);
  fclose(file);
  for(i = w ; i<strlen(concatenacion1); i++)
  {

  }
  free(codificacion);

}
