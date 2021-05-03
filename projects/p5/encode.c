/**This function contains the main code to run the encoding
scripts.  It takes two command line arguments, the first for
the file name of a 10X10 PGM, and the second for the name of the output file.

@author Zach Giles (zgiles)
@file image.c*/

#include "j10.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int main ( int argc, char *argv[] ) {
    if ( argc != 3 ) {
        fprintf( stderr, "usage: encode <input.pgm> <output.j10>\n" );
        exit( EXIT_FAILURE );
    }
    FILE *fp_open = fopen( argv[ 1 ], "r" );
    if ( !fp_open ) {
        perror( argv[ 1 ] );
        exit( EXIT_FAILURE );
    }

    BitWriter *writer = openBitWriter ( argv[ 2 ] );
    Image *im = readImage( argv[ 1 ] );
    encodeImage( im, writer );
    return EXIT_SUCCESS;

}