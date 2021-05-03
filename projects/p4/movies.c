/**This is the main program for the database project 4.  This program creates the watch
list, and contains the functionality to interact with that watchlist.  It also handles
parsing user commands to interact with the database and watch list.  User input is used
with functionality supplied by the input.h header, and database sorting commands are
accessed through the database.h header.  This program accepts at least one command
line argument that contains a file of database entries.

@file main.c
@author Zach Giles (zgiles)*/

#include "database.c"
#include "input.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <stddef.h>
#include <string.h>


/**List all entries of the watchlist.  This function is called when the user
enters the command line argument "list". No sort movies are listed as the were added
@param *dat the pointer to the watchlist to list all*/
static void listAllWL( Database *watchList ) 
{
    if (watchList -> count == 0 ) {
        printf("List is empty\n\n");
        return;
    }
    listDatabase( watchList, *isInTheDB, watchList );
}

/**Adds a Movie to the watchlist when the user commands add "move ID" if the movie isn't in the database this function handles the error
@param *dat the database of movies to pull from
@param movieID the id of the movie in the database
@param *watchList the watchlist struct to add the movie to from the db
@param *input the string of input given to the program from the user*/
static void add( Database *dat, int movieID, Database *watchList, char *input )
{
    for (int i = 0; i < (watchList -> count ); i++ ) {
        if ( ( (watchList -> dbPtr)[ i ] ) -> id == movieID ) {
            printf( "%s", input );
            printf("Movie %d is already on the watch list\n\n", movieID );
            return;
        }
    }
    for (int i = 0; i < ( dat -> count ); i++ ) {
        if ( ( ( dat -> dbPtr )[ i ] ) -> id == movieID ) {
            if ( ( ( watchList -> count ) >= ( watchList -> capacity ) ) ) {
                ( watchList -> capacity ) *= DOUBLE_CAP;
                ( watchList -> dbPtr ) = (Movie **)realloc( ( watchList -> dbPtr ), ( watchList -> capacity ) * sizeof( Movie * ) );
            }
            memcpy( ( (watchList -> dbPtr ) + ( watchList -> count ) ),  ( (dat -> dbPtr) + i ), sizeof( Movie *) );
            ( watchList -> count )++;
            printf( "%s\n", input );
            return;
        }
    }
    printf( "%s\n", input );
    printf( "Movie %d is not in the database\n", movieID );
}

/** This function removes a movie from the watch list. If movie isn't on watchlist this functions handles the error.
@param movieID the ID of the movie you want to remove from the watchlist
@param *watchList the watchlist to remove the movie from
@param *input the input from the uer*/
static void rem( int movieID, Database *watchList, char *input )
{
    //int initalCount = ( watchList -> count );
    for (int i = 0; i < ( watchList -> count ); i++ ) {
        if ( (  ( watchList -> dbPtr )[ i ] ) -> id == movieID ) { //if moive is on the watchlist
            //( ( watchList -> dbPtr )[ i ] ) = NULL; //set the watch list pointer at position i to null
            for (int j = i; j < ( watchList -> count ) - 1; j++ ) { //fill down the list from the node you just made null down to the end of the list
                ( (watchList -> dbPtr) [ j ] ) = ( ( watchList -> dbPtr )[ j + 1 ] );
            }
            ( watchList -> count )--; //remove one from the watch list count
            printf( "%s\n", input );
            return;
        }
    }
    printf( "%s", input );
    printf( "Movie %d is not on the watch list\n\n", movieID );
}

/**The movies main program accepts at least one command line argument for a file name of movies to build
a movie database from.  Multiple files can be entered as command line arguments and all of the movies will be added
to a single database.  After the db is created a watchlist is created.  After that a while loop is executed that 
continually prompts the user for commands that relate to viewing the database, filtering the datase by year, 
title, or genre.  The user can then build a watchlist from movies in the database by adding and removing
said movies from the watchlist.  User input of EOF, or the "quit" sentinel will exit the program
succesfully.
@param argc the number of files to add to the database
@param *argv[] an array of pointers to the command line arguments*/
int main( int argc, char *argv[] )
{
    if ( argc < 2 ) {
        fprintf( stderr, "usage: movies <movie-list>*\n" );
        exit( EXIT_FAILURE );
    }

    Database *dat = makeDatabase();
    //Database *watchList = makeDatabase();
    Database watchList;
    watchList.capacity = STARTING_CAP;
    watchList.dbPtr = (Movie **)malloc( ( dat -> capacity ) * sizeof( Movie * ) );
    watchList.count = 0;

    for ( int i = 1; i < argc; i++ ) {
        FILE *fp = fopen( argv[ i ], "r" );
        if ( !fp ) {
            fprintf( stderr, "Can't open file: %s\n", argv[ i ] );
            exit( EXIT_FAILURE );
        }
        readDatabase( dat, argv[ i ] );
        fclose( fp );
    }

    char *input;
    char comp[ SIZE_CHECK_TITLE ];
    int idCheck;
    char firstWord[ COMMAND_SIZE ];
    int minYear;
    int maxYear;
    char titleCheck[ CHAR_CHECK ];
    int pos;

    printf( "cmd> " );
    input = readLine( stdin );
    if ( input == NULL ) {
        free( input );
        freeDatabase( dat );
        exit( EXIT_SUCCESS );
    }
    sscanf( input, "%40s", comp ); //checks title length to see if it's longer than 38 characters, need to pull forty to check for 39 full characters with null terminator
    while ( strcmp( input, "quit\n" ) != 0  && input != NULL ) {

        if ( strcmp( input, "list\n" ) == 0 ) {
            printf( "list\n" );
            listAllWL( &watchList );
            printf( "cmd> " );
            free ( input );
            input = readLine( stdin );
            if ( input == NULL ) {
                free ( input );
                freeDatabase( dat );
                exit( EXIT_SUCCESS );
            }
            continue;
        }

        if ( strcmp( input, "database\n" ) == 0 ) {
            printf( "database\n" );
            listAll( dat );
            printf( "cmd> " );
            free ( input );
            input = readLine ( stdin );
            if ( input == NULL ) {
                free( input );
                freeDatabase( dat );
                exit( EXIT_SUCCESS );
            }
            continue;
        }

        if ( sscanf( input, "%6s%d", firstWord, &idCheck ) == 2 ) { 

            if ( strcmp( firstWord, "add" ) == 0 ) {
                //printf( "add %d\n\n", idCheck );
                add( dat, idCheck, &watchList, input );
                printf( "cmd> " );
                free ( input );
                input = readLine( stdin );
                if( input == NULL ) {
                    free( input );
                    freeDatabase( dat );
                    exit ( EXIT_SUCCESS );
                }
                continue;
            }


            if ( strcmp( firstWord, "remove" ) == 0 ) {
                rem( idCheck, &watchList, input );
                printf( "cmd> " );
                free ( input );
                input = readLine( stdin );
                if( input == NULL ) {
                    free( input );
                    freeDatabase( dat );
                    exit ( EXIT_SUCCESS );
                }
                continue;
            }
        }

    if ( sscanf( input, "%4s%d%d", firstWord, &minYear, &maxYear ) == 3 ) {
        if ( ( strcmp( firstWord, "year" ) == 0 ) && minYear <= maxYear) {
            printf("year %d %d\n", minYear, maxYear );
            listYear( dat, minYear, maxYear );
            printf( "cmd> " );
            free ( input );
            input = readLine( stdin );
            if( input == NULL ) {
                free( input );
                freeDatabase( dat );
                exit ( EXIT_SUCCESS );
            }
            continue;
        }

    }

    if ( sscanf( input, "%5s%1s%n", firstWord, titleCheck, &pos ) == 2 ) {
        if ( strcmp( firstWord, "title" ) == 0 )  {
            int newPos;
            int count = 0;
            char holder;
            sscanf(input + pos, "%[^ ]%n", &holder, &newPos );
            while ( holder != '\n' ) {
                count++;
                sscanf( input + pos, "%c%n", &holder, &newPos );
                pos += newPos;

            }
            count++; //null terminator
            char *secondWord = (char *)malloc( count * sizeof( char ) );
            sscanf( input, "%5s%s", firstWord, secondWord );

            printf("title %s\n", secondWord );
            listTitle( dat, secondWord );
            free( secondWord );
            printf( "cmd> " );
            free ( input );
            input = readLine( stdin );
            if( input == NULL ) {
                free( input );
                freeDatabase( dat );
                exit ( EXIT_SUCCESS );
            }
            continue;
        }
        if (strcmp( firstWord, "genre" ) == 0 ) {
            int newPos;
            int count = 0;
            char holder;
            sscanf( input + pos, "%[^ ]%n", &holder, &newPos );
            while( holder != '\n' ) {
                count++;
                sscanf (input + pos, "%c%n", &holder, & newPos );
                pos += newPos;
            }
            count++;
            char *secondWord = (char*)malloc( count * sizeof( char ) );
            sscanf( input, "%5s%s", firstWord, secondWord );

            printf("genre %s\n", secondWord );
            listGenre( dat, secondWord );
            free( secondWord );
            printf( "cmd> " );
            free ( input );
            input = readLine( stdin );
            if( input == NULL ) {
                free( input );
                freeDatabase( dat );
                exit ( EXIT_SUCCESS );
            }
            continue;
        }
    }

    if ( sscanf( input, "%40s", comp ) != 0 ) { // for blank lines
        printf("%s", input);
        printf( "Invalid command\n\n" );
        printf( "cmd> " );
        free ( input );
        input = readLine( stdin );
        if ( input == NULL ) {
            free ( input );
            freeDatabase( dat );
            exit ( EXIT_SUCCESS );
        }
        continue; 
    }

    free ( input );
    input = readLine( stdin );
}
    free( input );
    freeDatabase( dat );//free dat
    free(watchList.dbPtr);//then free wathclist pointer
    printf("quit\n");
    exit( EXIT_SUCCESS );
}