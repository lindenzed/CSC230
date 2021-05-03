/*
 * Just showing that unary operators -, ~ and ! all behave differently.
 */

#include <stdio.h>
#include <stdbool.h>

int main()
{
  // Some small variables to play with.
  signed char x, y, z, w;

  x = 0x1A;  // binary 00011010
  y = ~x;    // binary 11100101
  z = !x;    // binary 00000000
  w = -x;    // binary 11100110

  // We can check to see if this is true.
  // (I cast these to unsigned char here to
  // suppress sign extension)
  printf( "x: %x\n", (unsigned char) x );
  printf( "y: %x\n", (unsigned char) y );
  printf( "z: %x\n", (unsigned char) z );
  printf( "w: %x\n", (unsigned char) w );

  return 0;
}
