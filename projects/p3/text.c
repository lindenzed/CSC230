/**This program defines functions declared and globals declared in the
test.h header file.  It is used by the encrypt and decrypt programs
to read and write output after modifiing the text

@file text.c
@author Zach Giles (zgiles)*/
 
#include "text.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

int numberOfLines = 0;//global
char string[ MAXIMUM_ALLOWED_LINES ][ NUMBER_OF_CHARS_WITH_TERMINATOR ];//global

/**Reads the input file and stores it in the global char array
If the file cannot be read or doesn't exist the program exits
with a status of 1
@param *fp the file pointer used to scan the input*/
void readFile( FILE *fp ) 
{
    char holder[ NUMBER_OF_CHARS_WITH_TERMINATOR ];
    char ch;
    if ( !fp ) {
        exit( EXIT_FAILURE );
    }
    while ( numberOfLines < MAXIMUM_ALLOWED_LINES ) {
        /*fscanf(fp, "%c", &ch);
        printf("%c", ch);
        if (ch == '\n') {
            string[numberOfLines][0] = '\n';
            string[numberOfLines][1] = '\0';
            numberOfLines++;
            continue;
        }
        ungetc(ch, fp);*/
        ch = getc(fp);
        if (ch == '\n') {
            //ungetc(ch, fp);
            string[numberOfLines][0] = '\n';
            numberOfLines++;
            //fscanf(fp, "%*[\n]");
            continue;
        }
        ungetc(ch, fp);
        if ( fscanf( fp, "%100[^\n]", holder ) != 0 ) {//grabs up to 100 chars
            if ( strlen( holder ) + 1 == 101 ) {//if grabbed 100 chars add one to account for null terminator
                fscanf( fp, "%c", &ch );
                if ( ch != '\n' ) {//if next char after 100 chars isn't new line then line is too long
                    fprintf( stderr, "%s", "Line too long\n" );
                    exit( EXIT_FAILURE );
                }
                ungetc( ch, fp );//if the line is 100 characters then put the new line you grabbed back on
            }
            //fscanf( fp, "%*[\n]" );//move the scanner to the next line
            //getc(fp);

        }
        int holderLength = strlen( holder );
        //if ( numberOfLines != 0 ) {
        holder[ holderLength ] = '\n';
        holder[ holderLength + 1 ] = '\0';           
        //}
        //holder[ holderLength ] = '\n';
        //holder[ holderLength + 1 ] = '\0';
        strcpy( string[numberOfLines], holder );//copy the pulled row into the global array
        numberOfLines++;
        if ( fscanf(fp, "%*c%c", &ch) == EOF ) {//checks to see if at end of file
            break;
        }
        ungetc(ch, fp);
        //ungetc( ch, fp );//puts character back on stream
    }
    if ( fscanf( fp, "%s", holder ) != EOF ) {
        fprintf( stderr, "%s", "Too many lines\n" );
        exit( EXIT_FAILURE );
    }
    fclose(fp);
}

void writeFile( FILE *fp ) 
{
    for ( int i = 0; i < numberOfLines; i++ ) {
        int length = strlen( string[ i ] );
        //printf("%d", length);
        /*if ( length < 0 ) {
            fprintf( fp, "%c", '\n' );
            continue;
        }*/
        for ( int j = 0; j < length; j++ ) {
            fprintf( fp, "%c", string[ i ][ j ] );
        }
        //fprintf(fp, "%c", '\n');
    }
    fclose(fp);
}

/*int main() {
    FILE *fp = fopen("testinput.txt", "r");
    readFile(fp);
    for (int i = 0; i < numberOfLines; i++) {
        for (int j = 0; j < NUMBER_OF_CHARS_WITH_TERMINATOR; j++) {
            printf("%c", string[i][j]);
        }
        printf("%c", '\n');//add new line to end of line
    }
    fclose(fp);
}*/
