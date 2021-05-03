#include <stdio.h>
#include <stdbool.h>

int main( void )
{
  int x = 25;
  
  // Make an array with 3 elements.
  int a[ 3 ] = { 10, 20, 30 };

  int y = 50;

  // Look in array.
  printf( "Array a: %d %d %d\n", a[ 0 ], a[ 1 ], a[ 2 ] );

  // Look a little to the left.
  printf( "A little before a: %d %d\n", a[ -2 ], a[ -1 ] );

  // And a little to the right.
  printf( "A little after a: %d %d\n", a[ 3 ], a[ 4 ] );

  // --------- Curtain ------------

  // I had to add this line to keep the compiler from compiling out
  // x and y.  This was enough to make it leave space for them in
  // the stack frame, but it uses some things we haven't talked
  // about yet.  Pay no attention to the line behind the curtain.
  printf( "Where are you? %p %p %p\n", &x, a, &y );
}
