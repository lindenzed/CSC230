/*
 * Showing off underflow.  Floating point types can get only so close to zero.
 */

#include <stdio.h>
#include <stdbool.h>

int main()
{
  double denise = 1.0;

  // Keep trying to make smaller and
  // smaller values.
  while ( denise != 0.0 ) {
    printf( "%g\n", denise );
    denise = denise * 0.5;
  }

  return 0;
}
