// Demonstrating the relationship between array and pointer syntax.

#include <stdio.h>


int main()
{
  // An array.
  int a[ 6 ];

  // Get the addres of the start of this array.
  int *p = a;

  // Change the first element.
  a[ 0 ] = 5;

  // Change it via the pointer.
  *p = 10;

  printf( "%d\n", a[ 0 ] );

  // A evaluates to a pointer, so we can dereference it.
  *a = 5;

  printf( "%d\n", a[ 0 ] );

  return 0;
}
