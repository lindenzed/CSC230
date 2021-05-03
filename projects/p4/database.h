/**This is the header file for the database component for Project 4.
It declares the functions and structs used for creating a database
from a file and creating a watchlist of Movie structs.

@file database.h
@author Zach Giles (zgiles)*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#define LONG_STRING 3
#define SIZE_CHECK_TITLE 40 //used to pull in more than 38 characters to see if the 39th character is null terminator 
#define TITLE_SIZE 39 //39 so we can store 38 charactesrs and a null terminator
#define LINE_TOKEN_CHECK 3 //used to check that a read input line meets the format for a valid movie using return value for sscanf
#define COMMAND_SIZE 7 //maximum size of first word command calculated from "remove" with added room for null terminator
#define CHAR_CHECK 1 //used to test for a next string after the title command, using a string instead of char to skip whitepsace

/**Creates a struct for a Movie which will be filled
by the readDatabase function.*/
struct MovieStruct {
    char title[TITLE_SIZE];
    int id;
    int year;
    int length;
    char *genre;
};
typedef struct MovieStruct Movie;

/**Creates a struct for a Database which contains 
a pointer to a resizable array of pointers to Movies*/
struct DatabaseStruct {
    int capacity;
    int count;
    Movie **dbPtr;
};
typedef struct DatabaseStruct Database;

/**This function delcares and initializes a Database struct
@return a Database struct that will be filled by the readDatabase function*/
Database *makeDatabase();

/**This function is responsible for freeing the dynamically allocated
memory that was invoked in creating the Database
@param *dat the address of the Database object you want to free*/
void freeDatabase( Database *dat );

/**This function reads a datafile line by line and imports each line
as a Movie stuct.  It then stores the Movie structs in the Database
passed.
@param *dat the address of the Database you want to store the Movie structs in
@param *filename the filename of the input file passed as a string*/
void readDatabase( Database *dat, char const *filename );

/**This function list all of the movies in a Database struct sorted by ID
number.  The function will utilize qsort() and will internally cast the 
void pointers in qsort as pointers to Movie structs.
@param *dat the address of the Databse you want to list*/
void listAll( Database *dat );

/**This function will list all of the movies within the min/max year range
passed.  The Movie structs listed will be sorted by year, and then by ID.
@param *dat the address of the Database that you want to query.
@param min the min boundary for the query
@param max the max boundary for the query*/
void listYear( Database *dat, int min, int max );

/**This function list the Movie structs where the title field contains the string
passed to the function.  It does this using strstr() as mentioned in the project
description.  The movies will be sorted by ID.
@param *dat the address of the Database that you want to query.
@param *title the substring you are searching for passed as a pointer to a string literal*/
void listTitle( Database *dat, char const *title );

/**This function list the Movie structs where the genre field contains the string
passed to the function.  It does this using strstr() as mentioned in the project description.
The movies will be sorted by ID.
@param *dat the address of the Database that you want to query.
@param *genre the substring you are searching for passed as a pointer to a string literal*/
void listGenre( Database *dat, char const *genre );