#include <stdio.h>
#include <stdlib.h>

// Put your macro definitions here.  That should be all
// you need to do to complete this exercise.

#define DECL_LIST( double, list ) int list##_cap = 5; int list##_len = 0; double *list = ( double * )malloc( list##_cap * sizeof( double ) )
#define CHECK_CAP( double, list ) if( list_len >= list##_cap) { list##_cap *= 2; list = ( double * )realloc( list, list##_cap * sizeof( double) ); }
#define SIZE( list ) list##_len
#define FOR(i, condition) for(int i = 0; i < condition; i++)
#define SWAP(double, firstItem, secondItem) {double tmp = firstItem; firstItem = secondItem; secondItem = tmp;}


int main()
{
  // Make a resizable list.
  DECL_LIST( double, list );

  double val;
  while ( scanf( "%lf", &val ) == 1 ) {
    // Grow the list when needed.
    CHECK_CAP( double, list );

    // Add this item to the list
    list[ SIZE( list ) ] = val;
    SIZE( list ) += 1;
  }

  // Bubble-sort the list.
  FOR( i, SIZE( list ) )
    FOR( j, SIZE( list ) - i - 1 )
      if ( list[ j ] > list[ j + 1 ] )
        SWAP( double, list[ j ], list[ j + 1 ] );

  // Print out the resulting, sorted list, one value per line.
  FOR( i, SIZE( list ) )
    printf( "%.2f\n", list[ i ] );
  
  return EXIT_SUCCESS;
}
