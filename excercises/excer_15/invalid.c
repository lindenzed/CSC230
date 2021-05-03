// This is a bad program.  It reads and writes off the ends of a
// buffer it allocates with malloc.  This shows the "invalid read" and
// "invalid write" errors reported by valgrind.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  int *list = (int *)malloc( 10 * sizeof( int ) );
  
  // Reading off either end of this buffer will get valgrind's attention.
  int a = list[ 11 ];

  // So will writing off the end.
  list[ -1 ] =  a + 1;

  // Free the memory when we're done.
  free( list );
  
  return 0;
}
