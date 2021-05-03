// A trivial demonstration of malloc.  This isn't how you'd normally use it, but
// it shows how the mechanism works.

#include <stdio.h>
#include <stdlib.h>

int main()
{
  // Dynamically allocate space for 20 doubles.
  double *list = (double *)malloc( 20 * sizeof( double ) );

  // We can use this pointer like a 20-element array.

  // Fill it with something (otherwise, who knows what it contins)
  for ( int i = 0; i < 20; i++ )
    list[ i ] = i * 1.5;

  // Print out what we just put in the array.
  for ( int i = 0; i < 20; i++ )
    printf( "%d : %.2f\n", i, list[ i ] );

  // Free the memory for list, we're done with it.
  free( list );
  
  return 0;
}
