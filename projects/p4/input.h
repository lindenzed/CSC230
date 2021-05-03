/**This header declares the primary function used
to read an input file, line by line returning a string.

@author Zach Giles (zgiles)
@file input.h*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define STARTING_CAP 5
#define DOUBLE_CAP 2

/**The returned string can be used to validate the input file,
and create movie structs from valid input files.  This function performs
error handling if the input file cannot be read.

@param *fp a file pointer to the input file of movies used to create a movie database
@return A pointer to a string that can be used to create movie structs*/
char *readLine( FILE *fp );