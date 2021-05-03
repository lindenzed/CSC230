/*
  Program to demonstrate functions (vs inlining)
*/

#include <stdio.h>
#include <math.h>

// A poor approximation of PI
const double PI = 3.14;

// Return the volume of a height-h cylinder of radius r.
double volume( int h, int r )
{
  double v = h * r * r * PI;
  return v;
}

// Add up the areas of a bunch of cylinders.
int main( void )
{
  // Add them up.
  double total = 0.0;
  for ( int h = 0; h < 10000; h++ )
    for ( int r = 0; r < 10000; r++ )
      total += volume( h, r );

  // Report the total.
  printf( "%f\n", total );
}
