// Demonstration of fread()/fwrite() copy a file in blocks, rather
// than individual characters.  For really large files, this could be
// larger.

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
  FILE *src = fopen( argv[ 1 ], "rb" );
  if ( src == NULL ) {
    fprintf( stderr, "Can't open file %s for reading\n", argv[ 1 ] );
    return 1;
  }

  // Open the destination file for writing.
  FILE *dest = fopen( argv[ 2 ], "wb" );
  if ( dest == NULL ) {
    fprintf( stderr, "Can't open file %s for writing\n", argv[ 2 ] );
    return 1;
  }

  // Buffer for reading/writing from src/dest
  char buffer[ 1024 ];
  int len;
  while ( ( len = fread( buffer, 1, sizeof( buffer ), src ) ) != 0 )
    fwrite( buffer, 1, len, dest );

  // Close both the files.
  fclose( src );
  fclose( dest );

  return 0;
}
