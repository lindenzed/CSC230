/**This is the compilation unit for the Database header.  This unit
defines the functions in the header, and contains the static listDatabase
fucntion used by the other list functions which are then used by the 
movies component when database commands are passed through user input. 

@file database.c
@author Zach Giles (zgiles)*/

#include "database.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <stddef.h>
#include <string.h>


/**Comparison function to sort the database entries by ID
@param *aPtr a pointer to the array of pointers
@param *bPtr a pointer to the array of pointers
@return int negative if a is before b positive if b is before a zero if equal*/
static int idComp( const void *aPtr, const void *bPtr ) 
{
    Movie const *a = *( Movie ** )aPtr;
    Movie const *b = *( Movie ** )bPtr;
    if ( ( a -> id ) < ( b -> id ) ) {
        return -1;
    }
    if ( ( a -> id ) > ( b -> id )  ) {
        return 1;
    }
    return 0;
}

/**Comparison function to sort the database entries by year, if years are equal then sorting
is done by ID.
@param *aPtr a pointer to the array of pointers
@param *bPtr a pointer to the array of pointers
@return int negative if a is before b positive if b is before a zero if equal*/
static int yearComp( const void *aPtr, const void *bPtr ) 
{
    Movie const *a = *( Movie ** )aPtr;
    Movie const *b = *( Movie ** )bPtr;
    if ( ( a -> year ) < ( b -> year ) ) {
        return -1;
    }
    if ( (a -> year) > ( b -> year ) ) {
        return 1;
    }
    if ( ( a -> year ) == ( b -> year ) ) {
        if ( ( a -> id ) < ( b -> id ) ) {
            return -1;
        }
        if ( ( a -> id ) > ( b -> id ) ) {
            return 1;
        }   
    }
    return 0;
}

/**Prints the header for the database*/
static void printHeader() 
{
    printf( "%6s %38s %4s %3s\n", "ID", "Title", "Year", "Len" );
}

/**This function determines if a Movie is in a database based on the ID of the movie passed.
@param *mov Movie to check if the ID is found in the database
@param *data a pointer to a database of movies
@return true if the movie is in the database*/
static bool isInTheDB( const Movie *mov, const void *data ) 
{
    Database *dat = (Database *) data;
    for ( int i = 0; i < ( dat -> count ); i++ ) {
        if ( mov -> id == ( ( dat -> dbPtr )[ i ] )  -> id ) {
            return true;
        }
    }
    return false;
}

/*Struct to hold range of queried year range*/
struct Range {
    int rangeMin;
    int rangeMax;
};


/**This static function determines if a Movie is within the requested year range queried by the 
user when the "year" command is executed with appropiate arguments
@param *mov Movie to check if is within range
@param *data a struct containing the queried range
@return true if the movie is in the queried range*/
static bool isInYearRange ( const Movie *mov, const void *data ) 
{
    struct Range *yearRange = (struct Range *) data;
    if ( ( mov -> year ) >= ( yearRange -> rangeMin)  && ( mov -> year ) <= ( yearRange -> rangeMax ) ) {
        return true;
    }
    return false;
}

/**This static function determines if a Movie contains a string queried by the user in its
title when the "title" command is excecuted with appropiate arguments
@param *mov Movie to check if the title field contains the queried String
@param *data the string queried by the user
@return true if the movie title contains the queried string*/
static bool hasTitle ( const Movie *mov, const void *data ) 
{
    char *queriedTitle = (char *) data;
    if ( strstr( ( mov -> title ), queriedTitle ) != NULL ) {
        return true;
    }
    return false;
}

/**This static fucntion determines if a Movie contains a string queried by the user in its
genre field with the "genre" command is executred with appropate arguments
@param *mov Movie to check if the genre field contains the queried String
@param *data the string queried by the user
@return true if the movie genre contains the queried string*/
static bool hasGenre (const Movie *mov, const void *data )
{
    char *queriedGenre = (char *) data;
    if ( strstr( ( mov -> genre ), queriedGenre ) != NULL ) {
        return true;
    }
    return false;
}

/**This static function will be used by listAll, listYear and listTitle to run a 
boolean test to determine if the Movie struct passed to the test should
be printed on the list that is calling the function.  Each of the three
functions that use this will have a test function, and a pointer to the
respective test function is passed.  Each test function will accept a Movie
struct to run the test on along with a data parameter that will differ 
depending on which test is called.  The test function called will then
appropiately case the void data parameter to the appropiate type.
@param *dat the database that contains the Movie structs
@param (*test) a pointer to a test function
@param *data the void data parameter that will be passed to the test
function to be appropiately cast and used to determine the test conditions*/
static void listDatabase( Database *dat, bool (*test)( Movie const *movie, void const *data ), void const *data )
{
    int count = 0;
    for ( int i = 0; i < ( dat -> count ); i++ ) {
        if ( test( ( ( dat -> dbPtr )[ i ] ), data ) ) {
            char *thisTitle = ( dat -> dbPtr )[ i ] -> title;
            int thisId = ( dat -> dbPtr )[ i ] -> id;
            int thisYear = ( dat -> dbPtr )[ i ] -> year;
            int thisLength = ( dat -> dbPtr )[ i ] -> length;
            //char *thisGenre = ( dat -> dbPtr )[ i ] -> genre;
            if ( count == 0 ) {
                printHeader();

            }
            printf( "%6d %38s %4d %3d\n", thisId, thisTitle, thisYear, thisLength );
            count++;
        }
    }
    if ( count != 0 ) {
            printf("\n");
    }
    if ( count == 0 ) {
        printf( "No matching movies\n\n" );
    }
}

/*Constructor definition
@return a pointer to a dynamically allocated database of Movies database with default parameters
*/
Database *makeDatabase() 
{
    Database *dat = (Database *)malloc(sizeof( Database ) );
    dat -> capacity = STARTING_CAP;
    Movie **array = (Movie **)malloc( ( dat -> capacity ) * sizeof( Movie * ) );
    dat -> count = 0;
    dat -> dbPtr = array;
    return dat;
}

/**Frees dynamically allocated memory from database creation
@param *dat pointer to the dynamically allocated database to free*/
void freeDatabase( Database *dat ) 
{
    for ( int i = 0; i < ( dat -> count ); i++ ) {
        free( ( dat -> dbPtr) [ i ] -> genre ); //free movie genre
        free( ( dat -> dbPtr )[ i ] );
    }
    free( dat -> dbPtr );
    free( dat );
}

/**Reads a textfile into a dynamically allocated database
@param *dat pointer to the dynamically allocated database to store entries into
@param *filename pointer to the string that contains the filename to read*/
void readDatabase( Database *dat, char const *filename ) 
{
    FILE *fp = fopen( filename, "r" );
    if ( !fp ) {
        fprintf(stderr, "Can't open file: %s\n", filename );
        fclose( fp );
        freeDatabase( dat );
        exit( EXIT_FAILURE );
    }

    int i;
    char *line = readLine( fp );
    int pos1;
    int pos2;
    int pos3;
    int pos4;
    int thisId;
    char stringHolder[ SIZE_CHECK_TITLE ];//pull in extra characters to check string size
    int thisYear;
    int thisLength;

    while ( line != NULL ) {
        //if capacity if full double it
        if ( ( dat -> count ) >= ( dat -> capacity ) ) {
            ( dat -> capacity ) *= DOUBLE_CAP;
            ( dat -> dbPtr ) = (Movie **)realloc( ( dat -> dbPtr ), ( dat -> capacity ) * sizeof( Movie * ) );
        }

        //check line for valid input
        if ( sscanf( line, "%d%*[\t]%*[^\t]%*[\t]%d%d", &thisId, &thisYear, &thisLength ) != LINE_TOKEN_CHECK ) {
            fprintf( stderr, "Invalid movie list: %s\n", filename );
            free( line );
            fclose( fp );
            freeDatabase( dat );
            exit( EXIT_FAILURE );
        }


        //Duplicate ID check
        for (int i = 0; i < (dat -> count ); i++ ) {
            if ( ( dat -> dbPtr )[ i ] -> id == thisId ) {
                fprintf( stderr, "Duplicate movie id: %d\n", thisId );
                free( line );
                fclose( fp );
                freeDatabase( dat );
                exit( EXIT_FAILURE );
            }
        }

        //pull id in from read line
        sscanf( line, "%d%n", &thisId, &pos1 );
        //finish parsing string
        sscanf( line + pos1, "%*[\t]%40[^\t]%*[\t]%n", stringHolder, &pos2 ); //40 to check size of string
        if ( strlen( stringHolder ) <= 0 ) { //check empty string
            printf("Invalid move list: %s\n", filename );
            free ( line );
            fclose( fp );
            freeDatabase( dat );
            exit( EXIT_FAILURE );
        }
        int stringCounter = 0;
        char charCounter = sscanf( line + pos1, "%c%n", &charCounter, &pos3 ); //starting from ID grab the first character which is the first character of the title
        while ( charCounter != '\t' ) { //have to dynamically allocate string so numbers in the title aren't pulled in as the integer for the year
            stringCounter++; //in order to dynamically allocate you have to count the number of chars in the string
            pos1 += pos3;
            sscanf( line + pos1, "%c%n", &charCounter, &pos3 );
        }
        stringCounter++;//null terminator
        char *stringCounterPointer = (char *)malloc( (stringCounter ) * sizeof( char ) ); //allocate pointer to Title string
        sscanf( line, "%*[^\t]%*[\t]%[^\t]%d%d%n", stringCounterPointer, &thisYear, &thisLength, &pos4 ); //starting from ID pull in the title from dynamic allocated string, and year and length

        free( stringCounterPointer );//NEED TO MOVE THIS IF GENRE WORKS

        stringCounter = 0;
        pos1 = pos1 + pos4; //add pos 1 and pos 4 together to get to the beginning of the year
        pos1 = pos3;//make pos 3 the beginning of the year
        sscanf( line, "%*[^\t]%*[\t]%*[^\t]%*[\t]%*[^\t]%*[\t]%*[^\t]%*[\t]%c%n", &charCounter, &pos2 ); //pos3 now beginning of Genre
        stringCounter++;
        while ( charCounter != '\n' ) {
            stringCounter++;
            pos1 += pos2;
            sscanf( line + pos1, "%c%n", &charCounter, &pos2 );

        }
        stringCounter++; //null terminator
        char *genreCounterPointer = (char *)malloc(  stringCounter * sizeof( char )  );
        sscanf( line, "%*[^\t]%*[\t]%*[^\t]%*[\t]%*[^\t]%*[\t]%*[^\t]%*[\t]%s", genreCounterPointer );

        //for every valid line allocate memory for a movie
        ( dat -> dbPtr )[ dat -> count ] = (Movie *)malloc( sizeof ( Movie ) );//array notation

        //fill in Movie deets
        ( dat -> dbPtr )[ dat -> count ] -> genre = (char *)malloc( stringCounter * sizeof( char ) );
        strcpy( ( dat -> dbPtr )[ dat -> count ] -> genre, genreCounterPointer );
        strcpy( ( dat -> dbPtr )[ dat -> count ]  -> title, stringHolder);
        ( dat -> dbPtr )[ dat -> count ] -> id = thisId;
        ( dat -> dbPtr )[ dat -> count ] -> year = thisYear;
        ( dat -> dbPtr )[ dat -> count ] -> length = thisLength;

        free( genreCounterPointer );
        //check for oversize title
        if ( strlen( stringHolder ) > TITLE_SIZE - 1 ) { //minus 1 becuase strlen doesnt check null terminator 
            for ( i = 0; i < TITLE_SIZE - LONG_STRING; i++ ) {
                dat -> dbPtr[ dat -> count ] -> title[ i ] = stringHolder[ i ];
            }
            //format oversized title
            ( dat -> dbPtr[ dat -> count ] -> title )[ TITLE_SIZE - LONG_STRING ] = '.';
            ( dat -> dbPtr[ dat -> count ] -> title )[ TITLE_SIZE - LONG_STRING + 1 ] = '.';
            ( dat -> dbPtr[ dat -> count ] -> title )[ TITLE_SIZE - LONG_STRING + 1 + 1 ] = '\0';
        }

        //add movie to the count
        ( dat -> count )++;
        free( line );
        //continue reading
        line = readLine( fp );
    }
    free( line );
    fclose( fp );
}

/**List all entries of the database.  This function is called when the user
enters the command line argument "database". Sorting is done based on ID.
@param *dat the pointer to the database to list all*/
void listAll( Database *dat ) 
{
    qsort(  dat -> dbPtr, ( dat -> count ), sizeof( Movie * ), idComp );
    listDatabase( dat, *isInTheDB, dat );
}

/**List all entries in the database that are within a given year range.
This function is called when the user inputs the "year" command with arguments.  Sorting is done
based on the year of the movie, and by ID for movies with the same year.
@param *dat the pointer to the database to check for movies within the year range
@param min the lower bound of the year range
@param max the upper bound of the year range
*/
void listYear ( Database *dat, int min, int max ) 
{

    qsort(  dat -> dbPtr, ( dat -> count ), sizeof( Movie * ), yearComp );
    struct Range *yearRange = (struct Range *)malloc( sizeof ( struct Range ) );
    yearRange -> rangeMin = min;
    yearRange -> rangeMax = max;
    listDatabase( dat, *isInYearRange, yearRange );
    free( yearRange );
}

/**List all of the enteries in the database that contain the user inputed string in their 
"Title" field.  This functin is called when the user inputs the "title" command with arguments. Sorting is done
based on ID.
@param *dat the pointer to the database to check for movies with the queried title
@param *title pointer to the string of user input that serves as a movie title query*/
void listTitle( Database *dat, char const *title )
{
    qsort(  dat -> dbPtr, ( dat -> count ), sizeof( Movie * ), idComp );
    listDatabase( dat, *hasTitle, title );
}

/**List all of the entreis in the database that contain the user inputed string in their
"Genre" field.  This function is called when the user inputs the "title" command with arguments. Sorting is done
based on ID.
@param *dat the pointer to the database to check for movies with the queried genre
@param *genre pointer to the string of user input that serves as a movie genre query*/
void listGenre( Database *dat, char const *genre )
{
    qsort( dat -> dbPtr, ( dat -> count ), sizeof( Movie *), idComp );
    listDatabase( dat, *hasGenre, genre );
}
