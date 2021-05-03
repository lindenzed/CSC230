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

/*static bool inInTheWL( const Moive *mov, const void *data ) 
{
    Database *watchList = (Databse *) data;
    for ( int i = 0; i < ( watchList -> count ); i++ ) {
        if ( mov -> id == ( ( watchList -> dbPtr )[ i ] )  -> id ) {
            return true;
        }
    }
    return false;
}*/

/**List all entries of the watchlist.  This function is called when the user
enters the command line argument "list". No sort
@param *dat the pointer to the watchlist to list all*/
static void listAllWL( Database *watchList ) 
{
    if (watchList -> count == 0 ) {
        printf("list is empty\n");
        return;
    }
    printHeader();
    listDatabase( watchList, *isInTheDB, watchList );
}

static void add( Database *dat, int movieID, Database *watchList )
{
    for (int i = 0; i < (watchList -> count ); i++ ) {
        if ( ( (watchList -> dbPtr)[ i ] ) -> id == movieID ) {
            printf("Movie %d is already on the watch list\n", movieID );
            return;
        }
    }
    for (int i = 0; i < ( dat -> count ); i++ ) {
        if ( ( ( dat -> dbPtr )[ i ] ) -> id == movieID ) {
            if ( ( ( watchList -> count ) >= ( watchList -> capacity ) ) ) {
                ( watchList -> capacity ) *= DOUBLE_CAP;
                ( watchList -> dbPtr ) = (Movie **)realloc( ( watchList -> dbPtr ), ( watchList -> capacity ) * sizeof( Movie * ) );
            }
            printf( "add %d\n", movieID );
            memcpy( ( (watchList -> dbPtr ) + ( watchList -> count ) ),  ( (dat -> dbPtr) + i ), sizeof( Movie *) );
            ( watchList -> count )++;
            return;
        }
    }
    printf( "Movie %d is not in the database\n", movieID );
}

static void rem( int movieID, Database *watchList )
{
    //int initalCount = ( watchList -> count );
    for (int i = 0; i < ( watchList -> count ); i++ ) {
        if ( (  ( watchList -> dbPtr )[ i ] ) -> id == movieID ) { //if moive is on the watchlist
            ( ( watchList -> dbPtr )[ i ] ) = NULL; //set the watch list pointer at position i to null
            for (int j = i; j < ( watchList -> count ); j++ ) { //fill down the list from the node you just made null down to the end of the list
                ( (watchList -> dbPtr) [ j ] ) = ( ( watchList -> dbPtr )[ j + 1 ] );
            }
            ( watchList -> count )--; //remove one from the watch list count
            return;
        }
    }
    printf( "Movie %d is not on the watch list\n", movieID );
}
int main( int argc, char *argv[] )
{
    if ( argc < 2 ) {
        printf( "usage: movies <movie-list>*\n" );
        exit( EXIT_FAILURE );
    }

    Database *dat = makeDatabase();
    Database *watchList = makeDatabase();
    for ( int i = 1; i < argc; i++ ) {
        FILE *fp = fopen( argv[ i ], "r" );
        if ( !fp ) {
            printf( "Can't open file: %s\n", argv[ i ] );
            exit( EXIT_FAILURE );
        }
        readDatabase( dat, argv[ i ] );
    }

    char *input;
    char comp[ SIZE_CHECK_TITLE ];
    int idCheck;
    char firstWord[ COMMAND_SIZE ];


    printf( "cmd> " );
    input = readLine( stdin );
    if (input == NULL ) {
        exit( EXIT_SUCCESS );
    }
    sscanf( input, "%40s", comp );
    while ( strcmp( input, "quit\n" ) != 0 ) {

        if ( strcmp( input, "list\n" ) == 0 ) {
            printf( "list\n" );
            listAllWL( watchList );
            printf( "cmd> " );
            input = readLine( stdin );
            if ( input == NULL ) {
                exit( EXIT_SUCCESS );
            }
            continue;
        }

        if ( strcmp( input, "database\n" ) == 0 ) {
            printf( "database\n" );
            listAll( dat );
            printf( "cmd> " );
            input = readLine ( stdin );
            if ( input == NULL ) {
                exit( EXIT_SUCCESS );
            }
            continue;
        }

        if ( sscanf( input, "%6s%d", firstWord, &idCheck ) == 2 ) { 

            if ( strcmp( firstWord, "add" ) == 0 ) {
                add( dat, idCheck, watchList );
                printf( "cmd> " );
                input = readLine( stdin );
                if( input == NULL ) {
                    exit ( EXIT_SUCCESS );
                }
                continue;
            }


        if ( strcmp( firstWord, "remove" ) == 0 ) {
            printf( "remove %d\n", idCheck );
            rem( idCheck, watchList );
            printf( "cmd> " );
            input = readLine( stdin );
            if( input == NULL ) {
                exit ( EXIT_SUCCESS );
            }
            continue;
        }
    }
 
        if ( sscanf( input, "%40s", comp ) != 0 ) { // for blank lines
            printf( "Invalid command\n" );
            printf( "cmd> " );
            input = readLine( stdin );
            if ( input == NULL ) {
                exit ( EXIT_SUCCESS );
            }
            continue; 
        }


        input = readLine( stdin );
        if ( input == NULL ) {
            exit( EXIT_SUCCESS );
        }


    }

    /*add(dat, 32675, watchList );
    add(dat, 32676, watchList );
    add(dat, 9876, watchList );
    add(dat, 84082, watchList );
    add(dat, 32671, watchList );
    add(dat, 32672, watchList );
    add(dat, 32673, watchList );
    add(dat, 32674, watchList );

  
    listAllWL(watchList);
    rem( 32672, watchList );
    rem(9876, watchList);
    rem(84082, watchList);
    rem(32676, watchList);
    rem(32675, watchList);
    rem(32673, watchList);
    listAllWL(watchList);*/


    freeDatabase( dat );
    freeDatabase( watchList );
    printf("quit\n");
    exit( EXIT_SUCCESS );
}