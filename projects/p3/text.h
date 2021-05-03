/**This header file contians the functions and globals used in reading
a text file and writing the text to a 2D char array.

@file text.h
@author Zach Giles (zgiles)*/

#include <stdlib.h>
#include <stdio.h>

//Number of characters allowed per line is 100 add one for null terminator.
#define NUMBER_OF_CHARS_WITH_TERMINATOR 101

//The maximum number of lines allowed for a text file
#define MAXIMUM_ALLOWED_LINES 10000

//Declares the 2D array used to store the file text
extern char string[MAXIMUM_ALLOWED_LINES][NUMBER_OF_CHARS_WITH_TERMINATOR];

//Counter used for counting the lines in the input
extern int numberOfLines;

/**Function used to read the input file
@param *fp the file pointer used to scan the input*/
void readFile( FILE *fp );

/**Fucnction used to write the output file
@param *fp the file pointer used to write the output to a file*/
void writeFile( FILE *fp );
