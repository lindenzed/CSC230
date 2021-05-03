// Compare this example to multiDimensional.c  Here, we're showing analogous techniques
// for allocating lists of strings.  As one big 2D array, or as an
// array of char pointers (each pointing to a string).

#include <stdio.h>

// Here, we make a string list as a 2D array.
void twoDArray()
{
  char words[][ 14 ] = {
    "eggplant",
    "nap",
    "establishment",
    "synergy",
    "paleolithic",
    "seaweed"
  };

  // Here, each row has space for a 13-character string, even if we're not
  // using all that space.

  // Providing both indices will give you just a character.
  printf( "%c\n", words[ 3 ][ 1 ] );

  // Providing just one index will give you the starting address for
  // a row (i.e., a string)
  printf( "%s\n", words[ 4 ] );

  // We can get a pointer to the whole array, it's a pointer to
  // a sequence of 14-character arrays in memory.
  char (*wptr)[ 14 ] = words;
  
  // This pointer is just another way of getting to the contents of this 2D array.
  printf( "%s\n", wptr[ 5 ] );

  // This 2D array is writable, so we can change the contents of a string.
  words[ 5 ][ 3 ] = '\0';
  printf( "%s\n", words[ 5 ] );
}

// Here's alternative representation of the same information.  I put
// this in another function so I could re-use variable names.
void arrayOfPointers()
{
  // Here, we're making an outer array that really is an array of
  // char pointers, each pointing to a literal string.
  char *words[] = {
    "eggplant",
    "nap",
    "establishment",
    "synergy",
    "paleolithic",
    "seaweed"
  };

  // Here, each row/string is just taking the storage it needs.  The outer
  // array contains a pointer to the start of each string.

  // The outer index looks up the pointer to a string, we can index off this
  // to get an individual character
  printf( "%c\n", words[ 3 ][ 1 ] );

  // Providing just one index will give us a pointer to a literal string.
  printf( "%s\n", words[ 4 ] );

  // We can get a pointer to the whole array, it's a pointer to a pointer to char.
  char **wptr = words;
  
  // This pointer is just another way of getting to the contents of this 2D array.
  printf( "%s\n", wptr[ 5 ] );

  // But, the strings pointed to are each literal strings, so we can't write
  // to them.  This is the last thing this program does, so let's see what happens.
  words[ 5 ][ 3 ] = '\0';
  printf( "%s\n", words[ 5 ] );
}

int main()
{
  twoDArray();
  arrayOfPointers();
}
