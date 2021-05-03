/**
*/

#ifndef _IMAGE_H_
#define _IMAGE_H_

/** Magic number for the raw PGM format. */
#define PGM_MAGIC "P5"

/** Maximum intensity value expected for images. */
#define STD_RANGE 255

/** Representation for the contents of an image file. */
typedef struct {
  /** number of rows */
  int rows;
  
  /** pixels per row */
  int cols;
  
  /** Dynamically allocated pixel data, rows * cols pixels, each with
      an intensity value in the range 0..255.  This is stored as an array
      of pointers, each one pointing to a row of pixel data. */
  unsigned char **pix;
} Image;

/**This function will make an image struct and intialize it's fields with the
fields passed to the function dynammically allocating memory for the struct.
@param rows the number of rows in the pgm image file
@param cols the number of columns in the pgm image file
@return *makeImage a pointer to an image struct*/
Image *makeImage( int rows, int cols );

/**This function will create an Image struct pointer from the filename passed to it.
@param *filename a char pointer to a filename that contains a properly formatted PGM
image you want to store in an image struct.
@return an Image struct pointer.
*/
Image *readImage( char const *filename );

/**This function will write an Image struct to a PGM file
@param *image a pointer to an image struct you want to export as a PGM file
@param *filename the name you want to store the PGM file as */
void writeImage( Image *image, char const *filename );

/**This fucntions frees allocated memory associated with the Image struct pointer passed */
void freeImage( Image *image );
#endif
