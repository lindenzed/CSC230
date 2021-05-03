#include <stdio.h>
#include <stdbool.h>

int main()
{
  // Watch signed overflow happen.
  short sulley = 0;
  while ( true ) {
    sulley = sulley + 1;
    printf( "%d\n", sulley );
  }

  // We'll never get here, but we can think about
  // what would happen.
  unsigned short mike = 0;
  while ( true ) {
    mike = mike + 1;
    printf( "%d\n", mike );
  }

  return 0;
}
