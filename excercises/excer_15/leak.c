// This is a bad program.  It contains a memory leak and a file leak.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  // Two resources we're going to leak (but they will still
  // be reachable at program termiantion, easy to fix the leak).
  int *buffer = (int *)malloc( 10 * sizeof( int ) );
  FILE *fp = fopen( "output.txt", "w" );
  
  // Use these two resources
  buffer[ 0 ] = 25;
  fprintf( fp, "%d\n", buffer[ 0 ] );

  // Forget to free the memory and close the file.

  return 0;
}
