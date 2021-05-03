// Simplified code for resizing, using realloc.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// Read a list of integer values from standard input without knowing
// the length first.  This function dynamically allocates an array,
// and grows it as needed to accommodate more inputs.
int *readList( int *lenPtr )
{
  // Capacity in our array.
  int capacity = 5;
  
  // Number of array elements we're actually using
  int len = 0;

  // Allocate an array big enough to get us started.
  int *list = (int *)malloc( capacity * sizeof( int ) );

  // Keep reading integers.
  int val;
  while ( scanf( "%d", &val ) == 1 ) {
    // Grow the array if we're out of space.
    if ( len >= capacity ) {
      // Allocate a new, larger array
      capacity *= 2;
      list = (int *)realloc( list, capacity * sizeof( int ) );
    }
    
    // This is saying, we have enoguh space now.
    assert( len < capacity );
    
    list[ len++ ] = val;
  }

  *lenPtr = len;
  return list;
}

int main()
{
  // Read a dynamically allocated list from standard input.
  int len;
  int *list = readList( &len );

  // Print out the list, backward.
  for ( int i = len - 1; i >= 0; i-- )
    printf( "%d\n", list[ i ] );

  // Free the memory for list.
  free( list );
  
  return 0;
}
