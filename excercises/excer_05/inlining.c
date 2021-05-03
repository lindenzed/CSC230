/*
  Program to demonstrate inlining (vs functions)
*/

#include <stdio.h>
#include <math.h>

// A poor approximation of PI
const double PI = 3.14;

// Add up the areas of a bunch of cylinders.
int main( void )
{
  // Add them up.
  double total = 0.0;
  for ( int h = 0; h < 10000; h++ )
    for ( int r = 0; r < 10000; r++ )
      total += h * r * r * PI;

  // Report the total.
  printf( "%f\n", total );
}
