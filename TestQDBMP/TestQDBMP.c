#include "qdbmp.h"
#include <stdio.h>

int main( int argc, char* argv[] )
{
    BMP*    bmp;
    unsigned char   r, g, b;
    UINT    width, height;
    UINT    x, y, z;



    /* Read an image file */
    bmp = BMP_ReadFile("test.bmp");
    BMP_CHECK_ERROR( stderr, -1 ); /* If an error has occurred, notify and exit */

    /* Get image's dimensions */
    width = BMP_GetWidth( bmp );
    height = BMP_GetHeight( bmp );
    printf("Width: %lu Height:%lu\n",width,height);
    /* Iterate through all the image's pixels */
    z = 1;
    for ( x = 0 ; x < width ; ++x )
    {
        for ( y = 0 ; y < height ; ++y )
        {
            /* Get pixel's RGB values */
            BMP_GetPixelRGB( bmp, x, y, &r, &g, &b );

            printf("%lu- r:%lu, g:%lu, b:%lu \n",z,r,g,b);
            z++;

            /* Invert RGB values */

        }
    }

    /* Save result */
    /* Free all memory allocated for the image */
    BMP_Free( bmp );

    return 0;
}
