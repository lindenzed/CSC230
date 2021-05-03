/** This header file declares prototypes for the functions and structs
used by the bits component to read and write file input in bit strings.
Reading bits is accomplished by first creating a struct with a file
pointer and 32-bit buffer. The file pointer then utilizes the rb mode
string to read in the integers in bit mode using fread, and storing the 
read integer in the buffer.  Bit writing then accesses the binary stored in 
the writing Stucts and writes them to a file as bytes (unsigned char)

@author Zach Giles (zgiles)
@file bits.h*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**Definition of the BitReaderStruct incompletely 
declared in the header.  The Struct contains a file pointer
to the file it is reading from, a buffer that is 8 bits (uc),
and a bufferCounter that will allow us to traverse the buffer
bit by bit storing our current location.*/
struct BitReaderStruct {
    unsigned char *buffer;
    FILE *fp;
    int bufferCounter;
    bool ignoreHeader;
};
typedef struct BitReaderStruct BitReader;

/**Definition of the BitWriterStruct incompletely 
declared in the header.  The Struct contains a file pointer
to the file it is writing to, a buffer that is 8 bits (uc),
and a bufferCounter that will allow us to keep track of when
the buffer is full so we can write the bite to the file*/
struct BitWriterStruct {
    unsigned char *buffer;
    FILE *fp;
    int bufferCounter;
};
typedef struct BitWriterStruct BitWriter;

/** This function creates a BitReader Struct from a file name
if the file cannot be opened this function handles the error
@param *filename a char pointer to a file name that contains bytes
to be returned as bits
@return BitReader a bit reader struct that contains a file pointer
from the passed file name, and a 8-bit buffer to hold a read byte
to perform bitwise converstion.*/
BitReader *openBitReader( char const *filename );

/** This function closes a BitReader struct passed to it by
closing the file it's file pointer points to, and freeing
the memory allocated to its buffer.
@param *reader a pointer to a BitReader you want to free*/
void closeBitReader( BitReader *reader );

/**This fucntion returns the next bit from a BitReader.
If the buffer is empty it reads a byte and returns the first bit.
If the buffer contains bits it will return the next bit.
If there are no more bytes to read it returns EOF.
@param *reader a BitReader struct you want to read from
@return the next bit from the buffer as a 0 or 1 int*/
int getBit( BitReader *reader );

/**This function creates a BitWriter Struct that stores bits in its buffer
until a fully byte is assembled.  It then writes the byte to the file in the
file pointer.
@param *filename a char pointer to a file name you want to write the bytes to
@return BitWriter struct that contains a file pointer
from the passed file name, and an 8-bit buffer that contains bits to be returned
as bytes*/
BitWriter *openBitWriter( char const *filename );

/** This function closes a BitWriter struct passed to it by
closing the file it's file pointer points to, and freeing
the memory allocated to its buffer.
@param *writer a pointer to a BitWriter you want to free*/
void closeBitWriter( BitWriter *writer );

/** This function will access bits from the BitWriter passed
reading them one by one and storing them into a 8-bit buffer.
When the buffer is full it will write the value to its file pointer
@param *writer the Bit writer you want to get bits/bytes from.
@param val the value of the bit (1 / 0).*/
void putBit( BitWriter *writer, int val );