// Client program for the set implementation.
// Link this one with set-0

#include "set-0.h"
#include <stdio.h>

int main()
{
  // Initialize the set component.
  makeSet();

  // Put some values into the set.
  insertValue( 2 );
  insertValue( 3 );
  insertValue( 5 );
  insertValue( 7 );
  insertValue( 11 );
  
  // Print a report of values that are in the set, or not.
  for ( int i = 0; i <= 12; i++ )
    if ( containsValue( i ) )
      printf( "%d is in the set\n", i );
    else
      printf( "%d is not in the set\n", i );

  // We're done with the set component.
  destroySet();
}
