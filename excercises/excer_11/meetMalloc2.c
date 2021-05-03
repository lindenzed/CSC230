// A more realistic demonstration of malloc, read a list
// of integers and return a pointer to the list.
// You can redirect standard input to the file easy_input.txt

#include <stdio.h>
#include <stdlib.h>

// Read a list of integer values from standard input, first the length
// of the list, then the sequence of values on the list.  Return a
// pointer to the dynamically allocated list and put the length of the
// list in the len parameter.
int *readList( int *len )
{
  // Read the length of the list, no & here because len
  // is already a pointer to the storage we want scanf to modify
  scanf( "%d", len );

  // Allocate space for this list.
  int *list = (int *)malloc( *len * sizeof( int ) );

  // Read in all the values.
  for ( int i = 0; i < *len; i++ )
    // Note, pointer arithmetic to get the address of the ith element.
    scanf( "%d", list + i );

  return list;
}

// Comparison function for sorting ints.
int compar( const void *av, const void *bv ) {
  // Get the int values these pointers really point to.
  int a = *(int *)av;
  int b = *(int *)bv;
  
  // Compare them and return -1, 0, or 1 as appropriate
  if ( a < b )
    return -1;
  if ( a > b )
    return 1;
  return 0;
}

int main()
{
  // Read a dynamically allocated list from standard input.
  int len;
  int *list = readList( &len );

  // Let's use qsort to sort it, just for fun.
  qsort( list, len, sizeof( int ), compar );

  // Print out the conents of the list.
  for ( int i = 0; i < len; i++ )
    printf( "%d\n", list[ i ] );

  // Free the memory for list.
  free( list );
  
  return 0;
}
