// Showing off use of a variable-sized array

#include <stdio.h>
#include <stdbool.h>

#ifdef NEVER
// You can't do this for static arrays.  Length needs to be
// a compile-time constant.
int elements = 25;
int globalList[ elements ];
#endif

int main( void )
{
  int n;

  // Get the array size from the user.  We couldn't possibly
  // know this at compile time.
  printf( "How many values would you like: " );
  scanf( "%d", &n );

  // On the stack, we can allocate arrays with a size determined
  // during execution.
  int list[ n ];

  // How big is this array?  Normally, sizeof is evaluated at
  // compile-time, but here some of the work has to be done
  // at execution time.
  printf( "%zd\n", sizeof( list ) );
  
  // Put something in the array.
  for ( int i = 0; i < n; i++ )
    list[ i ] = i;

  return 0;
}
