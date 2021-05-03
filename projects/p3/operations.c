/**This program defines functions declared in the operations header

@file operations.c
@author Zach Giles (zgiles)*/
 
#include "operations.h"
#include "text.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

//int numberOfLines;//global
//char string[ MAXIMUM_ALLOWED_LINES ][ NUMBER_OF_CHARS_WITH_TERMINATOR ];//global


void swapLines( int m, int n ) 
{
    if ( m > numberOfLines || n > numberOfLines || m < 1 || n < 1 ) {
        //fprintf(stderr, "no");
        exit( EXIT_FAILURE );
    }
    int i;
    char temp1[ NUMBER_OF_CHARS_WITH_TERMINATOR ];
    char temp2[ NUMBER_OF_CHARS_WITH_TERMINATOR ];
    for ( i = 0; i < NUMBER_OF_CHARS_WITH_TERMINATOR; i++ ) {
        temp1[ i ] = string[ m - 1 ][ i ];
        temp2[ i ] = string[ n - 1 ][ i ];
    }
    for ( i = 0; i < NUMBER_OF_CHARS_WITH_TERMINATOR; i++ ) {
        string[ n - 1 ][ i ] = temp1[ i ];
        string[ m - 1 ][ i ] = temp2[ i ];
    }
}

void shiftLetters( int n )
{
    int i;
    int j;
    if ( n < -25 || n > 25 ) {
        //fprintf(stderr, "no");
        exit(EXIT_FAILURE);
    }
    for ( i = 0; i < numberOfLines; i++ ) {
        for ( j = 0; j < NUMBER_OF_CHARS_WITH_TERMINATOR; j++ ) {
            char ch;
            if ( string[ i ][ j ] <= 'Z' && string[ i ][ j ] >= 'A' ) {
                if ( string [ i ][ j ] + n > 'Z' ) {
                    int counter = 0;
                    while ( string[ i ][ j ] + counter < 'Z' ) {
                        counter++;
                    }
                    counter = n - counter;
                    ch = 'A' - 1;//minus one to account from shift from z to a
                    ch += counter;
                    string[ i ][ j ] = ch;
                    continue;
                }
                if ( string[ i ][ j ] + n < 'A' ) {
                    int counter = 0;
                    while ( string [ i ][ j ] + counter > 'A' ) {
                        counter--;
                    }
                    counter = n - counter;
                    ch = 'Z' + 1;
                    ch += counter;
                    string[ i ][ j ] =  ch;
                    continue;
                }
                else { 
                    ch = string[ i ][ j ];
                    ch += n;
                    string[ i ][ j ] = ch;
                    continue;
                }
            }
            if ( string[ i ][ j ] <= 'z' && string[ i ][ j ] >= 'a' ) {
                if ( string [ i ][ j ] + n > 'z' ) {
                    int counter = 0;
                    while ( string[ i ][ j ] + counter < 'z' ) {
                        counter++;
                    }
                    counter = n - counter;
                    ch = 'a' - 1;//minus one to account for shift from z to a
                    ch += counter;
                    string[ i ][ j ] = ch;
                    continue;
                }
                if ( string[ i ][ j ] + n < 'a' ) {
                    int counter = 0;
                    while ( string [ i ][ j ] + counter > 'a' ) {
                        counter--;
                    }
                    counter = n - counter;
                    ch = 'z' + 1;
                    ch += counter;
                    string[ i ][ j ] =  ch;
                    continue;
                }
                else {
                    ch = string[ i ][ j ];
                    ch += n;
                    string[ i ][ j ] = ch;
                    continue;
                }
            }
        }
    }
}

void reverseLines() 
{
    int i;
    int j;
    int k;
    for ( i = 0; i < numberOfLines; i++ ) {
        int length = strlen( string[ i ] );
        char temp[ length ];
        strcpy( temp, string[ i ] );
        for ( j = 0; j < length; j++ ) {
            string[ i ][ length - 1 - j ] = temp[ j ];
        }
        //if (string[ i ][ length - 1 ] == '\n' ) {
            //continue;
        //}
        //string[ i ][ length ] = '\n';
        //string[ i ][ length + 1 ] = '\0';
        char temp2[ length ];
        strcpy( temp2, string[ i ] );
        for (k = 0; k < length; k++ ) {
            string[ i ][ k ] = temp2[ k + 1 ];
        }
        string[ i ][ length - 1 ] = '\n';
        string[ i ][ length ] = '\0';
    }
}

void rotateLinesLeft()
{
    int i;
    int j;
    for ( i = 0; i < numberOfLines; i++ ) {
        int length = strlen( string[ i ] );
        char tempFirst = string[ i ][ 0 ];
        for ( j = 0; j < length - 1; j++ ) {
            string[ i ][ j ] = string[ i ][ j+1 ];
        }
        string[ i ][ length - 2 ] = tempFirst;
    }
}

void rotateLinesRight()
{
    int i;
    int j;
    for ( i = 0; i < numberOfLines; i++ ) {
        if ( string[ i ][ 0 ] == '\n' ) {
            continue;
        }
        int length = strlen( string[ i ] );
        char tempLast = string[ i ][ length - 2 ];
        for ( j = length - 2; j > 0; j-- ) {
            string[ i ][ j ] = string[ i ][ j - 1 ];
        }
        string[ i ][ 0 ] = tempLast;
    }
}


/*int main()
{
        FILE *fp = fopen("testinput.txt", "r");
    readFile(fp);
    for (int i = 0; i < numberOfLines; i++) {
        for (int j = 0; j < NUMBER_OF_CHARS_WITH_TERMINATOR; j++) {
            printf("%c", string[i][j]);
        }
        printf("%c", '\n');//add new line to end of line
    }
    printf("String 1:  %s\nString 5:  %s\n", string[0], string[4]);
    //swapLines(1, 0);
    //shiftLetters(-1);
    //reverseLines();
    //rotateLinesLeft();
    //rotateLinesRight();
    printf("String 1:  %s\nString 5:  %s\n", string[0], string[4]);
    fclose(fp);
}*/