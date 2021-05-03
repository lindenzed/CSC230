// A demonstration of functions from the C standard library that use
// pointers-to-functions.

#include <stdio.h>
#include <stdlib.h>

void goodbye()
{
  printf( "Goodbye World\n" );
}

int myComp( const void *a, const void *b )
{
  // Get the double values each of the parameters really
  // points to.
  double aval = *(double *)a;
  double bval = *(double *)b;

  // Get just the fractional part of the value.
  // This won't work for really big magnitudes.
  aval = aval - (int) aval;
  bval = bval - (int) bval;

  // Return negative or positive if one of these is larger.
  if ( aval < bval )
    return -1;
  if ( aval > bval )
    return 1;

  // They must be the same.
  return 0;
}

int main()
{
  // Register a function to call on exit.
  atexit( goodbye );

  // A list of doubles.
  double list[] = { 3.14,  9.32, 7.45, 81.30, 15.01, 99.67, 20.15 };

  // Sort them using my goofy comparison function, just comparing the fractional parts.
  qsort( list,                          // Start of the list
         sizeof(list)/sizeof(list[0]),  // number of items
         sizeof(double),                // size of each item
         myComp );                      // comparison function

  // See what we got.
  for ( int i = 0; i < sizeof(list)/sizeof(list[0]); i++ )
    printf( "%.2f ", list[ i ] );
  printf( "\n" );
    
  // Exit and see if your atexit function gets called.
  return 0;
}
