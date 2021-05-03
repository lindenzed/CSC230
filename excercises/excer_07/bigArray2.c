/*
  Test to see if we can have the same array
  as a global.
*/

#include <stdio.h>
#include <math.h>

int bigTable[ 100000000 ];

// Bill makes a really big array.
int bill()
{
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
