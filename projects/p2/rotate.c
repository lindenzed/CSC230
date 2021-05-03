/**
    This program rotates an input image 90 degrees
    and then outputs the rotated image to a file
    @file rotate.c
    @author Zach Giles (zgiles)
  */


#include "pgm.h"
#include <stdlib.h>
#include <stdio.h>


/**
Writes rotated image
@param height height of original image
@param width width of original image
@param pix array holding original image
@param newPix array to hold new image
*/
void writeImageRotate(int height, int width, unsigned char pix[ height] [width], unsigned char newPix[ width ] [ height ]){
    printf("%s", "P2\n");
    printf("%d %d\n", height, width);
    printf("%d\n", STD_RANGE);
    int i;
    int j;
    unsigned char temp[width][height];
    unsigned char temp2[width][height];
if (height >= width) {
    for (i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            temp[j][i] = pix[i][j];
        }
    }
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            temp2[i][j] = temp[i][j];
        }
    }
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            temp[i][j] = temp2[i][(height - 1) - j];
            pix[i][j] = temp[i][j];
            newPix[i][j] = pix[i][j];
        }
    }
}

if  (width > height) {
    for (i = 0; i < width; i++) {
        for(j = 0; j < height; j++) {
            temp[i][j] = pix[j][i];

        }
    }
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            temp2[i][j] = temp[i][j];
        }
    }
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            temp[i][j] = temp2[i][(height - 1) - j];
            newPix[i][j] = temp[i][j];
        }
    }
}
}
/**Rotates the image and writes to file*/
int main( void ) {
    checkType();
    int columns = readDimension();
    int rows = readDimension();
    checkRange();
    unsigned char pix[rows][columns];
    unsigned char newPix[columns][rows];
    readPixels(rows, columns, pix);
    writeImageRotate(rows, columns, pix, newPix);
    if (columns > rows) {
        writeImage(columns, rows, newPix);
    }
    else {
        writeImage(rows, columns, newPix);
    }
    return EXIT_SUCCESS;
}