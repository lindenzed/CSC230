// Demonstration of bit fields in a struct.

#include <stdio.h>

// Let's say we had particular capacities in mind for color components
// (maybe based on human perception).  We could spend particular numbers
// of bits on each value.
typedef struct {
  unsigned int red:9;
  unsigned int green:9;
  unsigned int blue:6;
  unsigned int alpha:6;
} PackedColor;

// Or, we could round up to the next sufficiently large type.
typedef struct {
  unsigned short red;
  unsigned short green;
  unsigned char blue;
  unsigned char alpha;
} RegularColor;

int main( int argc, char *argv[] )
{
  // See, just 4 bytes (on my system)
  printf( "Packed Size: %zd\n", sizeof( PackedColor ) );
  
  // If we couldn't do this, we would end up wasting some bits.
  printf( "Regular Size: %zd\n", sizeof( RegularColor ) );

  // We can use the packed struct like any other struct ...  mostly.
  PackedColor c1 = { 511, 256, 0, 32 };

  // We can access them.
  printf( "R: %u G: %u B: %u A: %u\n", c1.red,
          c1.green, c1.blue, c1.alpha );

  // We can change them ... maybe a little more blue.
  c1.blue += 16;

  printf( "R: %u G: %u B: %u A: %u\n", c1.red,
          c1.green, c1.blue, c1.alpha );

  // But, here we get overflow, in a 9-bit fields
  c1.red++;
  printf( "R: %u G: %u B: %u A: %u\n", c1.red,
          c1.green, c1.blue, c1.alpha );

#ifdef NEVER
  // But you can't take an address of one.  It may start in the middle
  // of a byte.
  void *ptr = &c1.red;
#endif
}
