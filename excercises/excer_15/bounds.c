// This is a bad program.  It uses heap-allocated and stack-allocated
// memory that's uninitialized.  For each, we try to access the array
// out of bounds.

#include <stdio.h>
#include <stdlib.h>

// A statically-allocated array
int staticArray[ 10 ];

int main()
{
  // A stack-allocated array
  int stackArray[ 10 ];

  // A heap-allocated array
  int *heapArray = (int *)malloc( 10 * sizeof( int ) );

  // Clear all these regions of memory. There's an out-of-bounds error
  // on the high end of each of these loops.
  for ( int i = 0; i <= 10; i++ )
    heapArray[ i ] = 0;

  for ( int i = 0; i <= 10; i++ )
    staticArray[ i ] = 0;

  for ( int i = 0; i <= 10; i++ )
    stackArray[ i ] = 0;

  // Free the dynamically allocted array.
  free( heapArray );
  
  return EXIT_SUCCESS;
}
