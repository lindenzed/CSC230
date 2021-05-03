/**This compilation unit defines the readLine fucntion in its
header.  The function can be used anytime the need for reading
an undefined line length of input and returning that line
as a pointer to a char array that contains that string.  This is done using dynamic
memory allocation.

@author Zach Giles (zgiles)
@file input.c*/

#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/**The returned string can be used to validate the input file,
and create movie structs from valid input files.  This function performs
error handling if the input file cannot be read.

@param *fp a file pointer to the input file of movies used to create a movie database
@return A pointer to a string that can be used to create movie structs*/
char *readLine( FILE *fp ) 
{
    char ch;
    int len = 0;
    int capacity = STARTING_CAP;
    char *string = (char *)malloc( capacity * sizeof( char ) );
    if ( fscanf( fp, "%c", &ch ) == EOF ) {
        free( string );
        return NULL;
    }
    while( ch != '\n' ) {
        if( len >= capacity ) {
            capacity *= DOUBLE_CAP;
            char *newString = (char *)malloc( capacity * sizeof( char ) );
            memcpy(newString, string, len * sizeof( char ) );
            free( string );
            string = newString;
        }
        string[ len++ ] = ch;
        fscanf( fp, "%c", &ch );
    }
    if ( len >= capacity - 1 ) {//checks to see if big enough to hold new line and null terminator
        capacity += DOUBLE_CAP;
        string = realloc( string, capacity * sizeof( char ) );
    }
    string[ len++ ] = '\n';
    string[ len++ ] = '\0';
    return string;
}
