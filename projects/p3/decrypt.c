/**This compilation unit will take command line arguments, and perform 
text manipulations based on them on the input file and output the manipulated
text to the output file, both declared by the last two command line arguments respectivley.
If - is entered in the input or output then it will use stdin or stdout.  This decrypt program
is designed to run certain operations in reverse of the encrypt program.

@file decrypt.c
@author Zach Giles (zgiles)*/

#include "text.c"
#include "operations.c"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>



//int numberOfLines;//global
//char string[ MAXIMUM_ALLOWED_LINES ][ NUMBER_OF_CHARS_WITH_TERMINATOR ];//global


/**The main program uses command line arguments to manipulate text in the input
file command line argument, and write the manipulated text to the output file 
indicated by file pointers. As long as the command line arguments are valid
any amount of arguments can be entered. This decrypt program is designed to run
certain operation in reverse of the encrypt program
@param argc the number of command line arguments
@param *argv[] the array of string pointers related to the command line arguments*/
int main( int argc, char *argv[] )
{
    bool reversed = false;
    int swappedInts[ argc ];
    int swappedCount = 0;
    int i;
if ( strcmp( argv[ argc - 2 ], "-" ) == 0 ) {
    readFile( stdin );
    //printf("stdin\n");
}
else {
    FILE *fp = fopen(argv[ argc - 2 ], "r" );
    if ( !fp ) {
        fprintf(stderr, "Can't open file: %s\n", argv[ argc - 2 ] );
        exit( EXIT_FAILURE );
    }
    readFile( fp );
    //printf("%s\n", argv[ i ]);
}

for ( i = 1; i < argc - 2; i++ ) {//first meaningful command line argument to the beginning of the input/output files

        if ( strcmp( argv[ i ], "swap" ) != 0 && strcmp( argv[ i ], "shift" ) != 0 && strcmp( argv[ i ], "reverse" ) != 0 && strcmp( argv[ i ], "left" ) != 0 &&
            strcmp( argv[ i ], "right" ) != 0) {
            fprintf( stderr, "invalid arguments\nusage: decrypt operation* (infile|-) (outfile|-)\n" );
            exit( EXIT_FAILURE );        
    }

    if ( strcmp( argv[ i ], "swap" ) == 0 ) {
        int parsed1 = atoi ( argv[ i + 1 ] );
        int parsed2 = atoi ( argv[ i + 2 ] );
        if ( parsed1 > numberOfLines || parsed2 > numberOfLines || parsed1 == 0 || parsed2 == 0 ) {
            fprintf( stderr, "invalid arguments\nusage: decrypt operation* (infile|-) (outfile|-)\n" );
            exit( EXIT_FAILURE );
        }
        swappedInts[ swappedCount ] = parsed1;
        swappedInts [ swappedCount + 1 ] = parsed2;
        swappedCount++;
        swappedCount++;
        //swapLines( parsed1, parsed2 );
        i++;
        i++;
        continue;
        //printf("swap\n");
    }


    if ( strcmp( argv[ i ], "shift" ) == 0 ) {
        int parsed = atoi ( argv [ i + 1 ] );
        if ( parsed < -25 || parsed > 25 || parsed == 0 ) {
            fprintf( stderr, "invalid arguments\nusage: decrypt operation* (infile|-) (outfile|-)\n" );
            exit( EXIT_FAILURE );
        }
        shiftLetters( -parsed );
        i++;
        continue;
        //printf("shift\n");
    }


    if ( strcmp ( argv[ i ], "reverse" ) == 0 ) {
        reverseLines();
        if ( !reversed ) {
            reversed = true;
        }
        else {
            reversed = false;
        }
        //printf("reverse\n");
    }

    if ( strcmp ( argv[ i ], "left" ) == 0 ) {
        if ( !reversed ) {
            rotateLinesRight();
            continue;
        }
        rotateLinesLeft();
        //printf("right\n");
    }


    if ( strcmp ( argv[ i ], "right" ) == 0 ) {
        if ( !reversed ) {
            rotateLinesLeft();
            continue;
        }
        rotateLinesRight();
        //printf("left\n");
    }


}

for ( int k = swappedCount; k > 0; k -= 2 ) {
    swapLines(swappedInts[ k - 1 ], swappedInts[ k - 2 ] );
}


if ( strcmp( argv[ i + 1 ], "-" ) == 0 ) {
    writeFile( stdout );
    //printf("stdout\n");
}
else {
    FILE *fp = fopen(argv[ i + 1 ], "w" );
    if( !fp ) {
        fprintf(stderr, "Can't open file: %s\n", argv[ i + 1 ] );
        exit( EXIT_FAILURE );
    }
    writeFile( fp );
    //printf("%s\n", argv[ i + 1 ]);
}
}