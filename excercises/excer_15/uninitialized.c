// This is a bad program.  It uses heap-allocated and stack-allocated
// memory that's uninitialized.  It does the same thing for statically-
// allocated memory, but that's guaranteed to be initialized, so it's
// not an error.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A statically-allocated array (initialized to zeros)
int staticArray[ 10 ];

int main()
{
  // A stack-allocated array (uninitialized)
  int stackArray[ 10 ];

  // A heap-allocated array (uninitialized)
  int *heapArray = (int *)malloc( 10 * sizeof( int ) );

  // Add up a value from each array.
  int total = 0;
  
  // This should be OK.
  total += staticArray[ 9 ];

  // This is an error, who knows what value we're getting.
  total += stackArray[ 9 ];

  // Also an errror, using uninitialized memory.
  total += heapArray[ 9 ];

  // Report the total.
  printf( "%d\n", total );

  // Free the memory when we're done.
  free( heapArray );
  
  return 0;
}
