/**
    This program creates a circular frame around the center
    of an image.
    @file frame.c
    @author Zach Giles (zgiles)
  */



#include "pgm.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define DIVDE_BY_TWO_DOUBLE 2.0
#define DIVDE_BY_TWO_INT 2
#define HALF_PIXEL 0.5

/**Finds the long radius
@param height height of image
@param width width of image
@return the longer radius
*/
double findLongCenter ( int height, int width) {
    int i;
    int longCounter = 0;
    double longCenter;
    if (width > height) {//long counter
        for(i = 0; i <= width; i++) {
            longCounter++;
        }
    }
    else {
        for (i = 0; i <= height; i++) {
            longCounter++;
        }
    }
    longCenter = longCounter / DIVDE_BY_TWO_DOUBLE;
    return (longCenter - HALF_PIXEL);
}
/**
Finds the shorter radius
@param height height of original image
@param width width of original image
@return the shorter radius
*/
double findShortCenter( int height, int width ) { 
    int i;
    int shortCounter = 0;
    double shortCenter;
    if (width > height) {//short counter
        for (i = 0; i <= height; i++) {
            shortCounter++;
        }
    }
    else {
        for (i = 0; i <= width; i++) {
            shortCounter++;
        }
    }
    shortCenter = shortCounter / DIVDE_BY_TWO_DOUBLE;
    return (shortCenter - HALF_PIXEL); //return shorter radius
}

/**
Finds the center of the rows
@param height height of image
@return the center of the rows
*/
double findRowCenter(int height) {
    int i;
    int rowCounter = 0;
    double rowCenter;
    for (i = 0; i <= height; i++) {
        rowCounter++;
    }
    rowCenter = rowCounter / DIVDE_BY_TWO_DOUBLE;
    return (rowCenter - HALF_PIXEL);
}
/**
Finds the center of the columns
@param width the width of the image
@return the center of the columns
*/
double findColumnCenter(int width) {
    int i;
    int columnCounter = 0;
    double columnCenter;
    for (i = 0; i <= width; i++) {
        columnCounter++;
    }
    columnCenter = columnCounter / DIVDE_BY_TWO_DOUBLE;
    return (columnCenter - HALF_PIXEL);
}

/**
Finds pixel distance from center
@param row row to finds distance of
@param column column to find distance of
@param imageCenter the center of the image
@param rowCenter the center of the rows
@param columnCenter the center of the columns
@param longCenter the longer radius
@param shortCenter the shorter radius
*/
double findPixelDistanceFromCenter(int row, int column, double imageCenter, double rowCenter, double columnCenter, double longCenter, double shortCenter) {
    double rowDistance = 0;
    double columnDistance = 0;
    double hypotenuse;
    column++;//Array starts at zero want actual column number
    row++;
    if (rowCenter == imageCenter) {
        if (((double) row - HALF_PIXEL) < shortCenter) {
            rowDistance = shortCenter - ((double) row - HALF_PIXEL);
        }
        if (((double) row - HALF_PIXEL) > shortCenter) {
            rowDistance = ((double) row - HALF_PIXEL) - shortCenter;
        }
        if (((double) column  - HALF_PIXEL) < longCenter) {
            columnDistance = longCenter - ((double) column - HALF_PIXEL);
            hypotenuse = sqrt((columnDistance * columnDistance) + (rowDistance * rowDistance));
            return hypotenuse;
        }
        if (((double) column - HALF_PIXEL) > longCenter) {
            columnDistance = ((double) column - HALF_PIXEL) - longCenter;
            hypotenuse = sqrt((columnDistance * columnDistance) + (rowDistance * rowDistance));
            return hypotenuse;
        }
        if (((double) column - HALF_PIXEL) == longCenter) {
            return 0;
        }
    }
    if (columnCenter == imageCenter) {
        if (((double) column - HALF_PIXEL) < shortCenter) {
            columnDistance = shortCenter - ((double) column - HALF_PIXEL);
        }
        if (((double) column - HALF_PIXEL) > shortCenter) {
            columnDistance = ((double) column - HALF_PIXEL) - shortCenter;
        }
        if (((double) row  - HALF_PIXEL) < longCenter) {
            rowDistance = longCenter - ((double) row - HALF_PIXEL);
            hypotenuse = sqrt((columnDistance * columnDistance) + (rowDistance * rowDistance));
            return hypotenuse;
        }
        if (((double) row - HALF_PIXEL) > longCenter) {
            rowDistance = ((double) row - HALF_PIXEL) - longCenter;
            hypotenuse = sqrt((columnDistance * columnDistance) + (rowDistance * rowDistance));
            return hypotenuse;
        }
        if (((double) row - HALF_PIXEL) == longCenter) {
            return 0;
        }
    }
    return 0;
}
/**
Frames the image by finding the pixels that should and shouldn't be included
If not included pixel is made white
*/
int main( void ) {
    checkType();
    int columns = readDimension();
    int rows = readDimension();
    checkRange();
    unsigned char pix[rows][columns];
    double shortCenter = findShortCenter(rows, columns);
    double longCenter = findLongCenter(rows, columns);
    double rowCenter = findRowCenter(rows);
    double columnCenter = findColumnCenter(columns);
    printf("%s", "P2\n");
    printf("%d %d\n", columns, rows);
    printf("%d\n", STD_RANGE);
    readPixels(rows, columns, pix);
    int count = 0;
    for (int i = 0; i < rows; i++) {
       for (int j = 0; j < columns; j++) {
            if (findPixelDistanceFromCenter(i, j, shortCenter, rowCenter, columnCenter, longCenter, shortCenter) > shortCenter) {
                int oldPixel = (int)(pix[i][j]);
                oldPixel = STD_RANGE;
                pix[i][j] = (unsigned char) (oldPixel);
                count++;
            }               
        }
    }
    if (rows > columns) {
            writeImage(rows, columns, pix);
    }
    else {
        writeImage(columns, rows, pix);
    }
    return EXIT_SUCCESS;
}