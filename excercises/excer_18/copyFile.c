// Demonstration of character input/output.  Used to copy a file
// character-by-character from a source file and a destination file
// given on the command line.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main( int argc, char *argv[] )
{
  // Make sure we get good command-line arguments.
  if ( argc != 3 ) {
    fprintf( stderr, "usage copyFile <src-file> <dest-file>\n" );
    return 1;
  }

  // Open the source file for reading.
  FILE *src = fopen( argv[ 1 ], "r" );
  if ( src == NULL ) {
    fprintf( stderr, "Can't open file %s for reading\n", argv[ 1 ] );
    return 1;
  }

  // Open the destination file for writing.
  FILE *dest = fopen( argv[ 2 ], "w" );
  if ( dest == NULL ) {
    fprintf( stderr, "Can't open file %s for writing\n", argv[ 2 ] );
    return 1;
  }

  // Copy characters until we hit EOF.
  int ch;
  while ( ( ch = fgetc( src ) ) != EOF )
    fputc( ch, dest );

  // Close both the files.
  fclose( src );
  fclose( dest );

  return 0;
}
