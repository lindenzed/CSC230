// Demonstration of functions from string.h, mostly string copy functions.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  // Make a few strings to work with.

  // This one will be null terminated.
  char name1[ 20 ] = "Bill";

  // This one is empty (but full of zeros, so it still has null termination).
  char name2[ 20 ] = {};

  // This one could be full of random bytes, without even a null terminator.
  char name3[ 20 ];

  // Make a big string, filled with copies of the alphabet.
  char big[ 200000 ];
  for ( int i = 0; i < sizeof( big ) - 1; i++ )
    big[ i ] = 'a' + i % 26;
  big[ sizeof( big ) - 1 ] = '\0';

  // Show off strlen
  printf( "name1 is %zd characters\n", strlen( name1 ) );

#ifdef NEVER  
  // this is a bad idea.  name3 isn't initialized.  It may
  // not even contain a null character.
  printf( "name3 is %d characters\n", strlen( name3 ) );
#endif

  // Count the number of z characters in the big string, just to have
  // something to do with it.

  // This is going to be slow, n^2
  int zcount = 0;
  for ( int i = 0; i < strlen( big ); i++ )
    if ( big[ i ] == 'z' )
      zcount++;

  // But, this will be much faster.
  zcount = 0;
  for ( int i = 0; big[ i ]; i++ )
    if ( big[ i ] == 'z' )
      zcount++;

  // Show off strcpy, copy a literal string into a char array.
  strcpy( name2, "Mary" );

  // Copy from one char array to another.
  strcpy( name3, name2 );

#ifdef NEVER  
  // But, this is going to cause a buffer overflow.
  strcpy( name2, big );
#endif

  // Strncpy lets us limit the bytes copied.
  strncpy( name2, big, sizeof( name2 ) - 1 );
  // Just in case we overflow, we'd still like this to
  // be a string.
  name2[ sizeof( name2 ) - 1 ] = '\0';

  printf( "%s\n", name2 );

  return 0;
}
