/**This function contains the main code to run the decoding
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
        fprintf( stderr, "usage: decode <input.j10> <output.pgm>\n" );
        exit( EXIT_FAILURE );
    }
    FILE *fp_open = fopen( argv[ 1 ], "r" );
    if ( !fp_open ) {
        perror( argv[ 1 ] );
        exit( EXIT_FAILURE );
    }



    BitReader *reader = openBitReader( argv[ 1 ] );



    int rows = 0x00000000;
    int cols = 0x00000000;
    if ( !(reader -> ignoreHeader) ) {

    for ( int i = 0; i < DIMENSION_BYTE; i++ ) {
        rows = rows << 1;
        rows = rows | getBit( reader );
    }

    for (int i = 0; i < DIMENSION_BYTE; i++) {
        cols = cols << 1;
        cols = cols | getBit( reader );
    }

    if (rows > 0x111 || cols > 111 ) {
        fprintf(stderr, "Invalid encoded file\n");
        exit( EXIT_FAILURE );
    }
    reader -> ignoreHeader = true;
}



    Image *im;

    for (int i = 0; i < rows; i += 10 ) {
    	for (int j = 0; j < cols; j += 10 ) {
    		    im = decodeImage( reader );
    		    writeImage( im, argv[ 2 ] );
    	}
    }



    return EXIT_SUCCESS;
}