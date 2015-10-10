#include "qdbmp.h"
#include <stdio.h>

int main( int argc, char* argv[] )
{
    BMP*    bmp;
    UCHAR   r, g, b;
    UINT    width, height;
    UINT    x, y;



    /* Read an image file */
    bmp = BMP_ReadFile("test.bmp");
    BMP_CHECK_ERROR( stderr, -1 ); /* If an error has occurred, notify and exit */

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

            printf("r:%i, g:%i, b:%i \n",r,g,b);

            /* Invert RGB values */

        }
    }

    /* Save result */
    /* Free all memory allocated for the image */
    BMP_Free( bmp );

    return 0;
}
