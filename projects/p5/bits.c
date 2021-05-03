/** This compilation unit defines methods in its header file.
This unit is used by the j10 component through the encode and decode
units.

@author Zach Giles (zgiles)
@file bits.c*/

#include "bits.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

#define LINES_TO_SKIP 3
//insert static functions here


/**Opens the BitReader pointer and intializes memory and fields for the pointer
@param *filename filename of the file you want to open in read bit mode for the 
BitReader to read.
@return a BitReader*/
BitReader *openBitReader ( char const *filename ) {
    FILE *fpReader = fopen( filename, "rb" );
    FILE *header = fopen( filename, "r" );
    if ( !header ) {
        perror( filename );
        exit( EXIT_FAILURE );
    }

    //Allocate dynamic memory for buffer
    unsigned char *readerBuffer = (unsigned char *)malloc( sizeof( unsigned char ) );
    
    //Create the BitReader
    BitReader *reader = (BitReader *)malloc( sizeof( BitReader ) );
    reader -> fp = fpReader;
    reader -> buffer = readerBuffer;
    reader -> bufferCounter = 0;
    reader -> ignoreHeader = false;
    fclose( header );
    return reader;
}

/**Closes dynamic memory allocated in creation of a BitReader
@param BitReader you want to free()*/
void closeBitReader( BitReader *reader ) {
    free( reader -> buffer );
    fclose( reader -> fp );
    free( reader );
}

/**Gets the next bit from a bit reader, or EOF
@param *reader a BitReader
@return int 0 or 1 depending on the value in the readers's buffer, or EOF*/
int getBit( BitReader *reader ) {
    unsigned char mask = 0x80;

    //Byte read trigger
    if ( reader -> bufferCounter == 0 ) {
        //error check while reading the byte
        if ( ! fread( reader -> buffer, sizeof( unsigned char ), 1, reader -> fp ) ) {
            return EOF;
        }

        //Return the first bit from the byte you just read
        if ( *(reader -> buffer) & mask ) {//if bit is 1
            ( reader -> bufferCounter )++;
            return 1;
        }
        ( reader -> bufferCounter )++;//if bit is 0
        return 0;
    }

    //if not the first byte we need to do some shifting
    else {
        if ( *( reader -> buffer) & mask >> ( reader -> bufferCounter ) ) {//shift the mask over to the digit we are working with
            ( reader -> bufferCounter )++;
            if ( reader -> bufferCounter == CHAR_BIT ) {//if buffer is full reset the counter
                ( reader -> bufferCounter = 0 );
            }
            return 1;
        }

        //if the bit read above wasn't 1/true register the 0 bit
        ( reader -> bufferCounter )++;
        if ( reader -> bufferCounter == CHAR_BIT ) {
            ( reader -> bufferCounter = 0 );
        }
        return 0;
    }
        //if this is the last bit reset the bufferCounter to trigger another byte read
        if ( reader -> bufferCounter == CHAR_BIT ) {
                ( reader -> bufferCounter = 0 );
        }
}

/** Creates a BitWriter pointer to an output file.
@param *filename to store the file to
@return pointer to a BitWriter*/
BitWriter *openBitWriter( char const *filename ) {
    FILE *fpWriter = fopen( filename, "wb" );
    if ( !fpWriter ) {
        perror( filename );
        exit( EXIT_FAILURE );
    }

    //fill in fields
    unsigned char *writerBuffer = (unsigned char *)malloc( sizeof( unsigned char ) );
    BitWriter *writer = (BitWriter *)malloc( sizeof( BitWriter ) );
    writer -> fp = fpWriter;
    writer -> buffer = writerBuffer;
    writer -> bufferCounter = 0;
    return writer;
}

/**Closes the BitWriter
@param *writer BitWriter pointer to free*/
void closeBitWriter( BitWriter *writer ) {
    free( writer -> buffer );
    fclose( writer -> fp );
    free( writer );
}

/**Writes the bit to the file
@param *writer the BitWriter that has the file pointer and buffer you are filling to write to bytes
@param int 0 or 1 depending on what value you are writing*/
void putBit( BitWriter *writer, int val ) {

    //if bit is 1
    if ( val ) {
        //if its the first bit
        if (writer -> bufferCounter == 0) {
            *( writer -> buffer ) = 0x80;
            ( writer -> bufferCounter )++;
        }
        //if its not the first bit
        else {
            //*(writer -> buffer) = *(writer -> buffer) >> 1;
            *(writer -> buffer) |= 0x80 >> ( writer -> bufferCounter );
            ( writer -> bufferCounter )++;
        }
    }

    //if bit is 0
    if ( !val ) {
        //if its the first bit
        if ( writer -> bufferCounter == 0 ) {
            *( writer -> buffer ) = 0x00;
            ( writer -> bufferCounter )++;
        }
        //if its not the first bit
        else {   
            //*( writer -> buffer ) >>= 1;
            ( writer -> bufferCounter )++;
        }
    }

    //if the buffer is full write the 8-bit buffer to a byte in the file
    if( writer -> bufferCounter == CHAR_BIT ) {
        fwrite( writer->buffer, sizeof(unsigned char), 1, writer -> fp);
        writer -> bufferCounter = 0;
    }
}
