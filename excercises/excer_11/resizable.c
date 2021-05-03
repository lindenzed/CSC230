// A smarter readList function, with a resizable array.  However,
// this one uses an inefficient technique for growing the array.
// It just grows it one element at a time.  This gets very expensive,
// O(n^2), if we have to read a long list of values.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Read a list of integer values from standard input without knowing
// the length first.  This function dynamically allocates an array,
// and grows it as needed to accommodate more inputs.
int *readList( int *lenPtr )
{
  // Capacity in our array.
  int capacity = 5;
  
  // Number of array elements we're actually using.
  // We could use the parameter, but this simplifies the syntax.
  int len = 0;

  // Allocate an array big enough to get us started.
  int *list = (int *)malloc( capacity * sizeof( int ) );

  // Keep reading integers.
  int val;
  while ( scanf( "%d", &val ) == 1 ) {
    // Grow the array if we're out of space.
    if ( len >= capacity ) {
      // Allocate another array, with greater capacity.
      capacity += 1;
      int *newList = (int *)malloc( capacity * sizeof( int ) );

      // Copy the contents of the old list to this new one.
      for ( int i = 0; i < len; i++ )
        newList[ i ] = list[ i ];

      // Now, free the old list and start using the new one.
      free( list );
      list = newList;
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
