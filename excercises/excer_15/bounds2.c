// This is a bad program.  It accesses static-, stack- and
// heap-allocated arrays out of bounds, but it does it via a function,
// so it's not as easy to detect through static analysis.

#include <stdio.h>
#include <stdlib.h>

// A function to fill an 11-element array with zeros.
void zeroFill( int *a )
{
  for ( int i = 0; i <= 10; i++ )
    a[ i ] = 0;
}

// A statically-allocated array
int staticArray[ 10 ];

int main()
{
  // A stack-allocated array
  int stackArray[ 10 ];

  // A heap-allocated array
  int *heapArray = (int *)malloc( 10 * sizeof( int ) );

  // Get our function to do the out-of-bounds reference to
  // these arrays.
  zeroFill( heapArray );
  zeroFill( staticArray );
  zeroFill( stackArray );


  // Free the dynamically allocted array.
  free( heapArray );
  
  return EXIT_SUCCESS;
}
