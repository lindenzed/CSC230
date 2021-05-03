// Client program for the set implementation.
// Link this one with set-1

#include "set-3.h"
#include <stdio.h>

// For comparing values.
bool sameInt( void const *v1, void const *v2 )
{
  // Look at these values as ints and see if they're the same.
  return *(int const *)v1 == *(int const *)v2;
}

int main()
{
  // Make a set, telling it the size of values we're going to use and
  // how to compare them.
  Set *s = makeSet( sizeof( int ), sameInt );

  // Put some values into it.  This part is a little ugly, since we can't
  // take the address of a literal value.  I'm making a single-element array for
  // each parameter, which evaluates to the address of that one element.
  insertValue( s, (int []){ 2 } );
  insertValue( s, (int []){ 3 } );
  insertValue( s, (int []){ 5 } );
  insertValue( s, (int []){ 7 } );
  insertValue( s, (int []){ 11 } );
  
  // But, we've given up on compile-time type checking here.  The following is
  // an error, but it would compile just fine.
#ifdef NEVER
  insertValue( s, (double []){ 3.14 } );
#endif
  
  // Print a report of values that are in the set, or not.
  for ( int i = 0; i <= 12; i++ )
    if ( containsValue( s, &i ) )
      printf( "%d is in the set\n", i );
    else
      printf( "%d is not in the set\n", i );

  // Free the set before we exit.
  destroySet( s );
}
