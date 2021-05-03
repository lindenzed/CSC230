/*
 * Showing off all the bitwise operators.
 */

#include <stdio.h>
#include <stdbool.h>

int main()
{
  // Some small variables to play with.
  unsigned char x, y;
  signed char z;

  x = 0x1A;  // binary 00011010
  y = ~x;    // binary 11100101

  // We can see the results (at least in hex)
  printf( "%x\n", y );

  // What do you think this will print.
  // Try it and see.  This isn't sign extension, it's just evidence
  // that even ~ is working on an int-sized version of y.
  printf( "%x\n", ~y );

  // You can do more than just characters.  It just
  // takes a lot of bits to write out the binary.
  unsigned long int ulysses = 0x3B294081D244C2B1UL;
  printf( "%lx\n", ~ulysses );

  x = 0x6C;
  y = 0xCA;

  // Now, show off the bitwise and, exclusive or and or.
  printf( "%x\n", x & y );
  printf( "%x\n", x ^ y );
  printf( "%x\n", x | y );

  // See, they're different from the logical and and or
  printf( "%x\n", x && y );
  printf( "%x\n", x || y );

  x = 0x1A;  // binary 00011010

  // Try just shifting one bit.
  printf( "%x\n", x << 1 );

  // Or, a few bits, see, this is performed in an unsigned
  // int.
  printf( "%x\n", x << 6 );

  // Or, a whole bunch.
  printf( "%x\n", x << 31 );

  x = 0xCA;  // binary 11001010
  z = 0xCA;  // also   11001010, but signed.

  // Try just shifting one bit.
  printf( "%x\n", x >> 1 );

  // Or, a few bits, see, this is performed in an unsigned
  // int.
  printf( "%x\n", x >> 3 );

  // Here, we get sign extionsion
  printf( "%x\n", z >> 3 );

  // For positive values, we can use bit shifting like multiply/divide
  printf( "%d\n", 75 << 2 );
  printf( "%d\n", 75 >> 2 );

  return 0;
}
