/*
 * Showing off float <-> integer conversion.
 */

#include <stdio.h>
#include <stdbool.h>

int main()
{
  // Some variables to work with.
  int ivan;
  float fran;

  // First, let's try float->int

  // Here's a float that will fit in an int exactly.
  fran = 208.0;
  ivan = fran;
  printf( "should be 208: %d\n", ivan );

  // Here's a float that the int can't represent
  // exactly.
  fran = 19.9999;
  ivan = fran;
  printf( "Won't be 19.9999: %d\n", ivan );

  // Here's a float that's too large to fit in an int.
  fran = 3000000000.0;
  ivan = fran;
  printf( "Won't be 3000000000: %d\n", ivan );

  // Now, let's try int->float

  // This one will fit in a float
  ivan = 194;
  fran = ivan;
  printf( "should be 194: %f\n", fran );

  // We don't have a float value for every possible int value that's this big.
  // We happen to have a representation for this value exactly.
  ivan = 67076092;
  fran = ivan;
  printf( "should 't be 67076092: %f\n", fran );

  // But, we can't represent this one exactly.
  ivan = 67076091;
  fran = ivan;
  printf( "won't be 392248671: %f\n", fran );

  return 0;
}
