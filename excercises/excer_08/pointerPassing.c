// Demonstration of pass-by-reference using pointers.

#include <stdio.h>

/** I take two int pointers, and swap the values they point to. */
void swap( int *x, int *y )
{
  // I could do this without the temp, but I don't want
  // to show off.
  int temp = *x;
  *x = *y;
  *y = temp;
}

/** We can mix parameter types.  Here, we take the first parameter as
    pass-by-address and the second as pass-by-valeu. */
void incrementBy( int *x, int y )
{
  *x += y;
}

/** In all these functions, it's really the pointers that are passed
    by value.  So, the function gets copies of the pointer the caller
    passes in, but it can't change the value of this pointer in the
    caller. */
void hulkSmash( int *x, int *y )
{
  x = NULL;
  y = NULL;
}

int main( void )
{
  // Some int variables to play with.
  int a = 25, b = 75, c = 125;

  // Try swapping these values.
  printf( "a = %d, b = %d, c = %d\n", a, b, c );

  // We have to remember to pass in the addresses.
  swap( &a, &b );

  printf( "a = %d, b = %d, c = %d\n", a, b, c );

  // As always, we can just pass values for value parameters.
  incrementBy( &c, 5 );

#ifdef NEVER
  // But we can't do this.  There's no address of a literal value (well, not in C)
  incrementBy( &5, a );
#endif

  // Get pointers for these three variables.
  int *ap = &a, *bp = &b, *cp = &c;

  // This function is expecting pointers.  If we already
  // have some, we can just pass them in.
  swap( ap, bp );

  // See, it swapped them back.
  printf( "a = %d, b = %d, c = %d\n", a, b, c );

  // We can think of pass-py-pointer as technique for pass-by-reference,
  // but we're just passing value that are, themselves, pointers.  The
  // subroutine can't change the contents of memory pointed to by these,
  // but it can't change where they point.
  hulkSmash( ap, bp );

  // See, that didn't hurt.
  printf( "a = %d, b = %d\n", *ap, *bp );
}
