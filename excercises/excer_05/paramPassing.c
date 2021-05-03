#include <stdio.h>
#include <math.h>

// Takes an double and returns an int.
int f( double x ) {
  return (int) ( x + 1 );
}

// Goes the other way.
double g( int x ) {
  return x + 1;
}

int main( void )
{
  int i1 = 5;
  double d1;

  // No problem here, we're going to wider types in both the
  // parameter and the return value.
  d1 = f( i1 );
  
  // Same here, but now we're going to narrower types.
  i1 = g( d1 );
  

  return 0;
}
