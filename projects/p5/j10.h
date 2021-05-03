/**This header file declares the two methods used for encoding and 
decoding a PGM/j10.

@author Zach Giles (zgiles)
@file j10.h*/

#ifndef _J10_H_
#define _J10_H_

#include "image.h"
#include "bits.h"
#define SCALE 0.044997

#define J10_BYTE_SIZE 7
#define DIMENSION_BYTE 12
#define DIMENSION_BITS 2 * DIMENSION_BYTE
#define INTENSITY_BYTE J10_BYTE_SIZE
#define J10_ELEMENTS 99
#define J10_BLOCK_CONSTANT DIMENSION_BITS + INTENSITY_BYTE + J10_ELEMENTS

#define HALF_CHAR CHAR_BIT / 2

/** Size of each image block used in the compressed image. */
#define BLOCK_SIZE 10

/**This function will encode an image in our j10 format to the 
file pointer in the BitWriter passed
@param *image the PGM image you want to encode
@param *writer the BitWriter used to encode the image in binary*/
void encodeImage( Image *image, BitWriter *writer );

/**This function will decode the j10 image that's in the
passed BitReader's file.
@param *reader a reader that has a j10 image pointer
@return Image* to the new decoded image*/
Image *decodeImage( BitReader *reader );
#endif
