// Comparison between array syntax for passing arrays and pointer
// syntax (they're just alternative ways of saying the same thing)

#include <stdio.h>

// Function that takes an array as a parameter.
void f( int a[] )
{
  // Manipulate the contents of the array a little bit.
  a[ 0 ] += 1;
  a[ 1 ] += 2;

  // Check the size of the array parameter (sure looks like a pointer).
  printf( "%zd\n", sizeof( a ) );

  // Move a two integers later, you couldn't do this with
  // an array.
  a += 2;
  a[ 0 ] += 3;
}

// Same logic, but with a different syntax for
// the parameter declaration.
void g( int *p )
{
  // Manipulate the contents of the array
  p[ 0 ] += 1;
  p[ 1 ] += 2;

  // Check the size of the parameter (no surprise, it looks like a pointer)
  printf( "%zd\n", sizeof( p ) );

  // Move a two integers later, you couldn't do this with
  // an array.
  p += 2;
  p[ 0 ] += 3;
}

int main()
{
  int list[] = { 1, 4, 9, 16, 25, 36, 49 };

  f( list );
  g( list );

  return 0;
}
