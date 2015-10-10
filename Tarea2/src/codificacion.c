#include "qdbmp.h"
#include <stdio.h>

int main( int argc, char* argv[] )
{
    BMP*    bmp;
    UCHAR  r, g, b;
    UINT    width, height;
    UINT    x, y;
    List pixeles;
    Node findeado;

    /* Read an image file */
    findeado = malloc(sizeof(Node));
    bmp = BMP_ReadFile("test.bmp");
    BMP_CHECK_ERROR( stderr, -1 ); /* If an error has occurred, notify and exit */
    pixeles = List_init(); // elementsize y la free function
    /* Get image's dimensions */
    width = BMP_GetWidth( bmp );
    height = BMP_GetHeight( bmp );
    /* Iterate through all the image's pixels */

    for ( x = 0 ; x < width ; ++x )
    {
        for ( y = 0 ; y < height ; ++y )
        {
            /* Get pixel's RGB values */
            BMP_GetPixelRGB( bmp, x, y, &r, &g, &b );
            if (!List_find(findeado,*r,*g,*b))
            {
              List_append(*r,*g,*b);
            }
            else
            {
              findeado.repeticiones++;
            }
        }
    }

    /* Save result */
    /* Free all memory allocated for the image */
    BMP_Free( bmp );

    return 0;
}
