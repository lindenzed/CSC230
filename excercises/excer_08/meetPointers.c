// Basic usage of pointers.

#include <stdio.h>

int main( void )
{
  // Make an int with a value in it.
  int a = 25;
  int b = 75;
  int c = 125;

  // Make a pointer to a.
  int *ptr = &a;

  // Now, use the pointer dereference operator to
  // get the value of the thing ptr points to.
  b = *ptr;
  printf( "%d\n", b );

  // Use the pointer dereference operator to change the
  // contents of the memory ptr points to.
  *ptr = -5;
  printf( "%d\n", a );

  // Make ptr point to a different integer.
  ptr = &c;
  // And print out the value ptr points to.  
  printf( "%d\n", *ptr );

  // I wonder what a pointer really looks like.
  printf( "%p\n", ptr );
}
