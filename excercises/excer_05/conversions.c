/*
 * Demonstration of the usual arithmetic conversions.
 */

#include <stdio.h>
#include <stdbool.h>

int main()
{
  // Some variables, to let us play with types and conversions.
  signed char c1, c2;
  short s1, s2;
  int i1, i2;
  long int l1;
  float f1, f2;

  // This would overflow if this sum was computed as a signed char.
  c1 = 126;
  c2 = 127;
  i1 = c1 + c2;

  // But, see, it doesn't
  printf( "%d\n", i1 );

  // Same here with short.
  s1 = 32766;
  s2 = 32767;
  i1 = s1 + s2;

  // See, the sum was comuted as two ints.
  printf( "%d\n", i1 );

  // In fact, that's why it's OK to do this.  The char and short types
  // are converted to int when we pass them to printf.
  printf( "%d %d\n", c1, s1 );

  // But, int doesn't automatically get promoted to long int, see.
  // We're assigning to a long, but the overflow occurs before the
  // assignment.
  i1 = 2147483646;
  i2 = 2147483647;
  l1 = i1 + i2;
  printf( "%ld\n", l1 );
  
  // But, we can get the compiler to promote first, if we help it out a little.
  l1 = (long) i1 + i2;
  printf( "%ld\n", l1 );
  
  // If either operand is some kind of floating point type, the other
  // will convert to a floating point type.
  i1 = 10;
  f1 = 10.1;
  f2 = i1 * f1;
  printf( "%f\n", f2 );
  
  // Even if the target of the assignment will discard the fraction,
  // the multiplication still happens in floating point.  Otherwise,
  // this would result in 100 instead of 101.
  i1 = 10;
  f1 = 10.1;
  i2 = i1 * f1;
  printf( "%d\n", i2 ); // See.

  return 0;
}
