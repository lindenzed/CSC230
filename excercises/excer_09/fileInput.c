// Reads a bunch of numbers from a file and prints their sum.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] )
{
  // Open a file for reading input.
  FILE *fp = fopen( "numbers.txt", "r" );

  // Complain if we can't open the inpt file.
  if ( !fp ) {
    fprintf( stderr, "Can't open input file\n" );
    exit( 1 );
  }

  // Total of the numbers.
  int total = 0;

  // Keep reading numbers until we can't match the pattern.
  int val;
  while ( fscanf( fp, "%d", &val ) == 1 )
    total += val;

  // Close the file.
  fclose( fp );

  // Print the total.
  printf( "Total: %d\n", total );

  return 0;
}
