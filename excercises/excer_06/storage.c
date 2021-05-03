#include <stdio.h>


// I will compile.
int x = 25;

#ifdef NEVER
// But not me.  Technically, I'm not initialized with a compile-time constant.
int y = x;
#endif

int main( void )
{
  // See, there's an auto keyword (that you never really need in C)
  auto int i = 5;
  printf( "%d\n", i );
}
