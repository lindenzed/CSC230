//
// Demonstration of the use of various values as conditional values..
//
#include <stdio.h>
#include <stdbool.h>

int main( void )
{
  // Here, we stop when i hits zero.
  int i1 = 10, i2 = 25;
  while ( i1 ) {
    printf( "Countdown: %d\n", i1 );
    i1--;
  }

  // This will compile just fine, but here, it will never stop.  
  // Because of floating point rounding behavior, f won't hit 0.0
  // exactly.  I'm using the preprocessor to exclude this from
  // the compiled program.
  double f1 = 1.0, f2 = 35.0;
#ifdef NEVER
  while ( f1 ) {
    printf( "Countdown: %f\n", f1 );
    f1 -= 0.1;
  }
#endif

  // If any value can be used as a boollean, 
  // C will happily convert anything to a bool variable.
  i1 = 10;
  bool b;
  b = i1;  // an int
  b = f1;  // a double
  b = ( i1 * 10 + f1 * 3.24 ) * f2; // whatever

  // Willingness to convert anything to bool works for operators also.
  // Notice, !!i1 is not the same as i1.
  printf( "%d %d %d\n", i1, !i1, !!i1 );

  // Same with reals, but maybe it's even stranger here.
  f1 = 10.0;
  printf( "%f %d %d\n", f1, !f1, !!f1 );

  // Notice, using a boolean operator pulls the value of our expression down
  // to the lowest-ranked type, _Bool

  // No surprise that the other logical operators also work on arbitrary values.

  // On int values.
  printf( "%d %d %d %d\n", 0 && 0, i1 && 0, 0 && i2, i1 && i2 );
  printf( "%d %d %d %d\n", 0 || 0, i1 || 0, 0 || i2, i1 || i2 );

  // On double values.
  printf( "%d %d %d %d\n", 0.0 && 0.0, f1 && 0.0, 0.0 && f2, f1 && f2 );
  printf( "%d %d %d %d\n", 0.0 || 0.0, f1 || 0.0, 0.0 || f2, f1 || f2 );

  // Using logical operators produces a _Bool output, even if its
  // parameters are higher-ranked types.
  printf( "%d\n", ( ( i1 * f1 ) && f2 ) * i2 );

  return 0;
}
