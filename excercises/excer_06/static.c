// Demonstration of variables with different scopes and lifetimes.

#include <stdio.h>

// A global variable, initialized at the start of program execution.
int x = 1;

// A recursive function, each call actually creates a new
// copy of its local variables.
void agitate( int d )
{
  // Two different ways to declare y. It has the same scope either
  // way, but different lifetimes and initialization behavior (i.e.,
  // a different storage class)

  // Allocate y statically.
  static int y = 10;

  // Or, allocate it on the stack.
  // int y = 10;

  // Depth limit on the recursion.
  if ( d < 4 ) {
    int z = 100;

    // Modify our three variables.
    x++;
    y++;
    z++;

    // Indent to show recursion depth.  I'm showing
    // off a format specifier here.  This isn't really
    // a good way to indent.
    printf( "%.*s", d, "          " );

    // Print all variable values.
    printf( "x = %d, y = %d, z = %d\n", x, y, z );

    // Make a recursive call, increasing the depth.
    agitate( d + 1 );
  }
}

int main()
{
  // Let our function do its thing.
  agitate( 0 );

  return 0;
}
