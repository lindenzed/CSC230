// Writing the contents of an array to a file, as binary.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main( int argc, char *argv[] )
{
  // Open the the output file in binary
  FILE *fp = fopen( "list.bin", "wb" );
  if ( fp == NULL ) {
    fprintf( stderr, "Can't open file list.bin for writing\n" );
    return 1;
  }

  // Array to write.
  int list[] = { 3, 472, 257381, 719293945 };

  // Write out the list, in one gulp.
  fwrite( list, sizeof( int ), sizeof( list ) / sizeof( int ), fp );

  // Close the destination file.
  fclose( fp );

  return 0;
}
