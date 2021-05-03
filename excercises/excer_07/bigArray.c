/*
  Test to see if a really big array will exceed our stack space.
*/

#include <stdio.h>
#include <math.h>

// Bill makes a really big array.
int bill()
{
  int bigTable[ 100000000 ];

  // I didn't really need the whole table.
  bigTable[ 0 ] = 1;
  return bigTable[ 0 ];
}

int main( void )
{
  // Call bill
  int x = bill();
  printf( "%d\n", x );
}
