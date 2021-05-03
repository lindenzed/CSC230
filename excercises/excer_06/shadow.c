// A demonstration of variable scope and shadowing.  Otherwise, not a
// useful or a good program.

#include <stdio.h>

// A couple of global variables.
int x = 6;
int y = 8;

// A function, so we can have local scopes and shadowing.
void waffle( int z )
{
  // Here, we shadow the global x.
  for ( int x = z; x < y; x++ ) {
    // Here, we shadow the parameter z.
    int z = x + y;
    if ( z <= 10 ) {
      // And here we shadow the local x declared earlier.
      int x = z * 2;
      printf( "%d %d %d\n", x, y, z );
    }
  }

  // Now, the global x is back in scope, but we shadow the global y.
  int y = x - 1;
  printf( "%d %d %d\n", x, y, z );
}

int main()
{
  waffle( 2 );

  // See, we can also access y (and x) from here.  They're global.
  y++;
  waffle( 1 );

  return 0;
}
