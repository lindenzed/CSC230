// Demo writing output to a file.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main( int argc, char *argv[] )
{
  // Open a file for output.
  FILE *fp = fopen( "output.txt", "w" );

  // Complain if we can't create the output file.
  if ( !fp ) {
    fprintf( stderr, "Can't open output file\n" );
    exit( 1 );
  }

  // Write some double values to a file, 
  for ( int i = 0; i < 25; i++ )
    fprintf( fp, "%f\n", i * i * 3.141592653589793 );

  // Close the file.
  fclose( fp );

  return 0;
}
