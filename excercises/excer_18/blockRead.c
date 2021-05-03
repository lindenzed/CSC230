// Reading the contents of an array from a file, as binary.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main( int argc, char *argv[] )
{
  // Open the input file in binary
  FILE *fp = fopen( "list.bin", "rb" );
  if ( fp == NULL ) {
    fprintf( stderr, "Can't open file list.bin for reading\n" );
    return 1;
  }

  // Array to write read (we're cheating by pretending we know the size.
  int list[ 4 ];

  // Write out the list, in one gulp.
  fread( list, sizeof( int ), sizeof( list ) / sizeof( int ), fp );

  // Close the destination file.
  fclose( fp );

  // See what we got.
  for ( int i = 0; i < sizeof( list ) / sizeof( int ); i++ )
    printf( "%d ", list[ i ] );
  printf( "\n" );

  return 0;
}
