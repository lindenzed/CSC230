/** This comilation unit defines the methods in its header file.  It also included two other
methods that typically would be static but aren't for the purposes of automated testing.
This program will contain the neccessary code to encode and decode PGM files to a compressed
"j10" binary format

@author Zach Giles (zgiles)
@file j10.c*/

#include "j10.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>




/**This method will compute the discrete cosine transform (DCT) of a 
10 X 10 block of PGM data.
@param X an array of doubles that will hold the pixel data of a PGM image to be transformed
@parm Y an array of doubles that will store the transformed PGM data*/
void DCTBlock( double X[ BLOCK_SIZE ][ BLOCK_SIZE ], double Y[ BLOCK_SIZE ][ BLOCK_SIZE ] ) {
    double Sm;
    double Sn;
    for (int m = 0; m < BLOCK_SIZE; m++ ) {
        for (int n = 0; n < BLOCK_SIZE; n++ ) {
            Sm = ( m == 0 )?( 1 / M_SQRT2 ):1;
            Sn = ( n == 0 )?( 1 / M_SQRT2 ):1;
            double sum = 0;
            double sigmaJ = 0;
            for ( int i = 0; i < BLOCK_SIZE; i++ ) {
                for (int j = 0; j < BLOCK_SIZE; j++ ) {
                    sigmaJ = cos( ( M_PI / BLOCK_SIZE ) * ( i + 0.5 ) * m ) * 
                    cos( ( M_PI / BLOCK_SIZE ) * ( j + 0.5 ) * n ) * X[ i ][ j ];
                    sum += sigmaJ;
                }
            }
            Y[ m ][ n ] = sum * (double)SCALE * ( 2 / (double)BLOCK_SIZE) * Sm * Sn;
        }
    }
}

void IDCTBlock( double Y[ BLOCK_SIZE ][ BLOCK_SIZE ], double X[ BLOCK_SIZE ][ BLOCK_SIZE ] ) {
    double Sm;
    double Sn;
    for (int m = 0; m < BLOCK_SIZE; m++ ) {
        for (int n = 0; n < BLOCK_SIZE; n++ ) {
            double sum = 0;
            double sigmaJ = 0;
            for ( int i = 0; i < BLOCK_SIZE; i++ ) {
                for (int j = 0; j < BLOCK_SIZE; j++ ) {
                    Sm = ( i == 0 )?( 1 / M_SQRT2 ):1;
                    Sn = ( j == 0 )?( 1 / M_SQRT2 ):1;
                    sigmaJ = Sm * Sn * cos( ( M_PI / BLOCK_SIZE ) * ( m + 0.5 ) * i ) * 
                    cos( ( M_PI / BLOCK_SIZE ) * ( n + 0.5 ) * j ) * Y[ i ][ j ];
                    sum += sigmaJ;
                }
            }
            X[ m ][ n ] = sum * ( 1 / (double)SCALE ) * ( 2 / (double)BLOCK_SIZE);
        }
    }
}
/**Enodes a PGM image to a compressed j10 binary format
@param image the PGM image to encode
@param writer the BitWriter that will wrtie the binary data*/
void encodeImage( Image *image, BitWriter *writer ) {

    int temp = ( image -> rows );
    //temp = temp << CHAR_BIT;
    for ( int i = 0; i < HALF_CHAR; i++ ) {
        putBit( writer, temp & 0X800 >> i ); //first 4 bits in first byte
    }
    temp = ( image -> rows );
    //temp = temp >> HALF_CHAR;
    for ( int i = 0; i < HALF_CHAR; i++ ) {
        putBit( writer, temp & 0X800 >> ( i + HALF_CHAR ) ); //second 4 bits in first byte
    }
    temp = ( image -> rows );
    for ( int i = 0; i < 4; i++ ) {
        putBit( writer, temp & 0X800 >> ( i + CHAR_BIT ) ); //first 4 bits in second byte
    }
    temp = ( image -> cols );
    //temp = temp >> CHAR_BIT;
    for ( int i = 0; i < HALF_CHAR; i++ ) {
        putBit( writer, temp & 0X800 >> i ); //second 4 bits in second byte
    }
    temp = ( image -> cols );
    //temp = temp >> HALF_CHAR;
    for ( int i = 0; i < HALF_CHAR; i++ ) {
        putBit( writer, temp & 0X800 >> ( i + HALF_CHAR ) );//first 4 bits in third byte
    }
    temp = ( image -> cols );
    for ( int i = 0; i < HALF_CHAR; i++ ) {
        putBit( writer, temp & 0X800 >> ( i + CHAR_BIT ) ); //second 4 bits in third byte
    }

   //printf("Rows: %d Cols: %d\n", image->rows, image->cols);
    int counter = 0; //used to count the number of non zero entities so that we can figure out how many final 0's to add
    double X[ BLOCK_SIZE ][ BLOCK_SIZE ] = {};
    double Y[ BLOCK_SIZE ][ BLOCK_SIZE ] = {};

    //int max = ( image -> rows > image -> cols )?(image->rows):(image->cols);
    //int min = ( image -> cols > image -> rows )?(image -> rows ):( image -> cols );

    for (int PGM_rows = 0; PGM_rows < image -> rows; PGM_rows += BLOCK_SIZE ) {
        for ( int PGM_cols = 0; PGM_cols < image -> cols; PGM_cols += BLOCK_SIZE ) {
            //printf("%d %d\n", PGM_rows, PGM_cols );
            //Get the pixels for the DCT
            for (int i = 0; i < BLOCK_SIZE; i++ ) {
                for (int j = 0; j < BLOCK_SIZE; j++ ) {
                    X[ i ][ j ] = ( image -> pix )[ i + PGM_rows ][ j + PGM_cols ];
                }
            }

            DCTBlock( X, Y ); //run DCT on pic

            //round DCT to nearest interger value
            int Z[ BLOCK_SIZE ][ BLOCK_SIZE ];
            for (int i = 0; i < BLOCK_SIZE; i++ ) {
                for (int j = 0; j < BLOCK_SIZE; j++ ) {
                    Z[ i ][ j ] = (int)round( Y[ i ][ j ] );
                }
            }


            unsigned char intensity = Z[ 0 ][ 0 ];//top left value
            unsigned char mask = 0x80 >> 1;//mask for 7 bit
            for ( int i = 0; i < J10_BYTE_SIZE; i++ ) {
                putBit( writer, intensity & mask >> i );//top left 7-bit
            }
            putBit( writer, Z[ 0 ][ 1 ] );//second bit

            for ( int i = 2; i < BLOCK_SIZE; i++ ) {//8 bits left in first row
                if ( Z[ 0 ][ i ] != 0 ) {
                    putBit( writer, 1 );
                }
                else {
                    putBit( writer, 0 );
                }
            }

            for ( int i = 1; i < BLOCK_SIZE; i++ ) {//every row after first row
                for ( int j = 0; j < BLOCK_SIZE; j++ ) {
                    if ( Z[ i ][ j ] != 0 ) {
                        putBit( writer, 1 );
                    }
                    else {
                        putBit( writer, 0 );
                    }
                }
            }

            unsigned short bigMask = 0x8000 >> 10; //make unsigned short mask to deal with int which will be cast to unsigned short
            //counter = 0; //used to count the number of non zero entities so that we can figure out how many final 0's to add
            for (int i = 0; i < BLOCK_SIZE; i++ ) {
                for (int j = 0; j < BLOCK_SIZE; j++ ) {
                    if ( i == 0 && j == 0) { //if on the top left corner skip it
                        j++;
                    }
                    if ( Z[ i ][ j ] != 0 ) { 
                        counter++;
                        if ( Z[ i ][ j ] < 0 ) { //if negative
                            putBit( writer, 1 );
                        }
                        else { //if positive
                            putBit( writer, 0 );
                        }
                        for ( int k = 0; k < J10_BYTE_SIZE - 1; k++ ) {
                            putBit( writer, (unsigned short)abs((Z[ i ][ j ])) & bigMask >> k ); //use abs since we already accounted for the sign
                        }
                    }
                }
            }
        }
    }

            //int finalZeros = abs ( ( 8 - ( 106 % 8 ) ) - ( ( counter * 7 ) % 8 ) );
                int finalZeros = abs( ( ( ( J10_BLOCK_CONSTANT ) + ( counter * J10_BYTE_SIZE ) ) % CHAR_BIT ) - CHAR_BIT );
            while ( finalZeros ) {
                putBit( writer, 0 );
                finalZeros--;
            }

}

/**Decodes a j10 image to PGM formaet
@param *reader the BitReader that will create the PGM image
@return an image in PGM format*/
Image *decodeImage( BitReader *reader ) {
    int rows = 0x00000000;
    int cols = 0x00000000;
    int topLeft;
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


        int values [][ 2 ] = {}; //hold positions of values for non zeros

        int counter = 0;  //Count non-zero's

        for (int i = 0; i < J10_BYTE_SIZE; i++ ) { //gets the first int in the top left corner
            topLeft = topLeft << 1;
            topLeft = topLeft | getBit( reader );
        }

        double Z[ BLOCK_SIZE ][ BLOCK_SIZE ] ={};
        Z [ 0 ][ 0 ] = topLeft; // fill in first square

        for ( int i = 1; i < BLOCK_SIZE; i++ ) {
            Z[ 0 ][ i ] = getBit ( reader ); //find non-zeros on first row
            if ( Z[ 0 ][ i ] != 0) {
                values[ counter ][ 0 ] = 0;
                values[ counter ][ 1 ] = i;
                counter++;
            }
        }

        for ( int i = 1; i < BLOCK_SIZE; i++ ) {
            for ( int j = 0; j < BLOCK_SIZE; j++ ) { //find non-zeros on other rows
                Z[ i ][ j ] = getBit( reader );
                if ( Z[ i ][ j ] != 0) {
                    values[ counter ][ 0 ] = i;
                    values[ counter ][ 1 ] = j;
                    counter++;
                }
            }
        }

        for ( int i = 0; i < counter; i++ ) {
            int byte = 0;
            bool isNegative = false;
            if ( getBit( reader ) ) { 
                isNegative = true; //if first bit is one then it's negative
            }
            for (int j = 0; j < J10_BYTE_SIZE - 1; j++ ) { //read the 6 bit value
                byte = byte | getBit( reader );
                if ( j < J10_BYTE_SIZE - 2 ) {
                    byte <<= 1;
                }
            }
            if ( isNegative ) {
                Z[ values[ i ][ 0 ] ] [ values[ i ][ 1 ] ] = -byte;
            }
            else {
                Z[ values[ i ][ 0 ] ] [ values[ i ][ 1 ] ] = byte;   
            }

        }


        double Y[ BLOCK_SIZE ][ BLOCK_SIZE ] = {}; //holds inverse DCT
        unsigned char X[ BLOCK_SIZE ][ BLOCK_SIZE ] = {}; //holds chars from inverse DCT
        IDCTBlock( Z, Y ); //inverse DCT

        for ( int i = 0; i < BLOCK_SIZE; i++ ) { 
            for ( int j = 0; j < BLOCK_SIZE; j++ ) {
                if ( Y[ i ][ j ] > STD_RANGE ) {
                    Y[ i ][ j ] = STD_RANGE; //upper bound
                }
                if ( Y[ i ][ j ] < 0 ) { //lower bound 
                    Y[ i ][ j ] = 0;
                }
                X[ i ][ j ] = (unsigned char)round( Y[ i ][ j ] );  //cast rounded doubles to unsigned char
            }
        }

        Image *im = makeImage( 10, 10 );
        //writeImage( im, "output.pgm");
        for ( int i = 0; i < BLOCK_SIZE; i++ ) {
            for ( int j = 0; j < BLOCK_SIZE; j++ ) {
                (im -> pix)[ i  ] [ j  ] = X[ i ][ j ];
            }
        }

    return im;
}
