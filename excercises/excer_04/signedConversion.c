/*
 * Showing off what happens when signed/unsigned values overflow.
 */

#include <stdio.h>
#include <stdbool.h>

int main()
{
  // Some variables to play with.
  short sulley;
  unsigned short mike;

  // Nothing bad going on here.
  sulley = 5;
  mike = sulley;
  printf( "Should be 5: %u\n", mike );

  // Here ... well mike can't store negative numbers.
  sulley = -2;
  mike = sulley;
  printf( "Can't be -2: %u\n", mike );

  // We can have the same problems going the other way.
  mike = 15;
  sulley = mike;
  printf( "Should be 15: %d\n", sulley );

  // Similar problems here, sulley can't hold really big values
  // For this example, we're assuming short is 16 bits.
  mike = 65532;
  sulley = mike;
  printf( "Probably won't be 64432: %d\n", sulley );

  return 0;
}
