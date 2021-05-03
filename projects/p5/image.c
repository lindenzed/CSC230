/** This program defines the methods in the image.h header.  It is used to make Image structs that the
user can store PGM images into.  Once in the struct the values can be more easily accessed and 
manipulated for compression.

@author Zach Giles (zgiles)
@file image.c*/

#include "image.h"
#include <stdio.h>
#include <stdlib.h>


/**Function used to exit the program from various header checks of a PGM file*/
void static exitHeader() {
    fprintf( stderr, "%s", "Invalid image file\n" );
    exit( EXIT_FAILURE );
}
//insert static functions here




/** Allocate space for the array of pointers based on number of rows, and then
allocate space for each pointer in the array based on the number of columns.
This struct is able to store pixels associated with a PGM file.
@param rows the number of rows in the PGM file
@parm cols the number of cols in the PGM file
@Return a pointer to an Image struct that hasn't been intialized*/
Image *makeImage( int rows, int cols ) {
    //allocate the pointer array
    unsigned char **pix = (unsigned char **)malloc( rows * sizeof( unsigned char (*)[ cols ] ) );
    //allocate the image
    Image *im = (Image *)malloc( sizeof( Image ) );
    //allocate the char arrays in the pointer array
    for ( int i = 0; i < rows; i++ ) {
        (pix)[i] = (unsigned char *)malloc( cols * sizeof( unsigned char ) );
    }
    im -> rows = rows;
    im -> cols = cols;
    im -> pix = pix;
    return im;
}

/**This function will initalize the memory in the Image struct that was previously
allocated based on the text falues in the file name.  Handles errors for files.
@param *filename a pointer to a filename
@return an Image struct that has been intialized.*/
Image *readImage( char const *filename ) {
    FILE *fp = fopen( filename, "rb" );
    if ( !fp ) {
        perror( filename );
        exit( EXIT_FAILURE );
    }

    //pull in the header
    int rows;
    int columns;
    int intensity;
    //Header Error Checking
    if ( fgetc( fp ) != 'P' ) {
        exitHeader();
    }
    if ( fgetc( fp ) != '5' ) {
        exitHeader();
    }
    if ( fscanf( fp, "%d%d%d%*c", &columns, &rows, &intensity ) != 3 ) {
        exitHeader();
    }

    if ( (columns > 0x111) | (rows > 0x111) ) {
        exitHeader();
    }
    if ( intensity != STD_RANGE ) {
        exitHeader();
    }

    if ( columns % 10 != 0 || rows %10 != 0 ) {
        exitHeader();
    }
    //make the Image
    Image *im = makeImage( rows, columns );
    //for each row fill in the columns
    for ( int i = 0; i < rows; i++ ) {
        for ( int j = 0; j < columns; j++ ) {
            ( im -> pix )[ i ] [ j ] = fgetc( fp );
        }
    }
    fclose( fp );
    return im;
}

/**This function will write an initialized image to the PGM file name passed
@param *image the Image struct with PGM data you want to write to file
@param *filename the filename you want to save the PGM image to*/
void writeImage( Image *image, char const *filename ) {
    FILE *fp = fopen( filename, "w" );
    if ( !fp ) {
        perror( filename );
        exit( EXIT_FAILURE );
    }
    //header
    fputc( 'P', fp );
    fputc( '5', fp );
    fputc( '\n', fp );
    fprintf( fp, "%d %d\n", image -> cols, image -> rows );
    fprintf(fp, "%d\n", STD_RANGE );

    //for each row print the chars in the columns
    for ( int i = 0; i < image -> rows; i++ ) {
        for ( int j = 0; j < image -> cols; j++ ) {
            fputc( ( ( image -> pix )[ i ] )[ j ], fp );
        }
    } 
    fclose( fp );   
}

/**This function will free the memory allocated to an Image struc
@param *image the Image struct you want to free*/
void freeImage( Image *image ) {
    for ( int i = 0; i < image -> rows; i++ ) {
        free( ( image -> pix)[ i ] );
    }
    free( image -> pix );
    free( image );
}
