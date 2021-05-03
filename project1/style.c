/**
    @file style.c
    @author Zach Giles (zgiles)
    This is a test program provided to us by the teaching staff/faculty.
    The program intially contained style errors, and our task is to correct them.
*/

#include <stdio.h>
#include <stdlib.h>

/** The maximum length a printed line can be*/
#define MAX_LENGTH 72

/**Prints a 'word' consisting of random characters
    @param x the length you want the 'word' to be
*/
void printWord( int x )
{
    for ( int i = 0; i < x; i++ ){
            // Print a random lower-case letter.
            printf( "%c", 97 + rand() % 26 );
    }
}

/**Prints a line of 'words' up to a limited length and then
    returns the length of the line.
*/
int printLine() {
    int count = 0, pos = 0, space = 0;
    int len = 1 + rand() % 10;
    // Print a line of words up to a limited length.
    while ( pos + len + space < MAX_LENGTH) {
        if ( space > 0 ) {
            printf( " " );
        }
        printWord( len );
        pos += len + space;
        len = 1 + rand() % 10;
        space = 1;
        count += 1;
    }
    printf( "\n" );
    return count;
}

/**Prints a paragraph consisting of lines of 'words'.
    @param n the number of lines in the paragraph
    @return total the total number of 'words' in the paragraph
*/
int printParagraph( int n )
{
    int total = 0;
    for ( int i = 0; i < n; i++ )
    total += printLine();
    return total;
}

/**Runs the main program and prints a paragraph of 10 lines of 'words'
    Also prints the total words in the paragraph.
    @return 0 if success
*/
int main(){int w=printParagraph(10);printf("Words: %d\n",w);return 0;}