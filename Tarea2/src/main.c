//##############################################################################
//
//                                  Tarea 2
//
//                       Oscar Estay   -   Bastian Mavrakis
//
//##############################################################################

#include "filemanager.h"

int main(int argc, char *argv[]) {
    if(argc != 4){
        printf("El programa se ejecuta de la forma:\n");
        printf("./tarea2 modo imagen.bmp comprimido.bin\n");
        printf("Donde:\n");
        printf("---------\n");
        printf("modo = 0 -> Compresion\n");
        printf("modo = 1 -> Descompresion\n");
    }
    if(!strcmp(argv[1], "0")){
        Compress_BMP(argv[2], argv[3]);
    }

    return 0;
}
