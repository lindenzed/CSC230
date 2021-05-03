// A list of up to 100 words, each one dynamically allocated and accessed
// via an array of char pointers.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Read a sequence of tokens (words) from standard input, storing
// them in list and returning the number of words read.
int readWords( char *words[], int capacity )
{
  int count = 0;

  // Keep reading and storing words until we get them all or
  // we reach capacity.  Each word can be up to 99 characters.
  char str[ 100 ];
  while ( count < capacity &&
          scanf( "%99s", str ) == 1 ) {
    // Get just enough space for this word (including the termiantor)
    words[ count ] = (char *) malloc( strlen( str ) + 1 );
    strcpy( words[ count ], str );
    count++;
  }

  // Tell the caller how many we got.
  return count;
}

int main()
{
  // Room for 100 words (char pointers).
  char *words[ 100 ];
  
  // Read all the words.
  int count = readWords( words, sizeof( words ) / sizeof( words[ 0 ] ) );

  // Print them all out, one per line.
  for ( int i = 0; i < count; i++ )
    printf( "%s\n", words[ i ] );

  // The words array is stack allocated, but each word is dynamically allocated.
  // Someone should free all these words.  It's us.
  for ( int i = 0; i < count; i++ )
    free( words[ i ] );

  return 0;
}
