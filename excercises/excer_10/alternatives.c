// Showing different alternatives for accessing array elements via pointers.

#include <stdio.h>

int stringLen1( char const *str );
int stringLen2( char const *str );

int main()
{
  // List of values to work with.
  int a[] = { 1, 4, 9, 16, 25 };
  int len = sizeof( a ) / sizeof( a[ 0 ] );
  int sum;

  // Plain-old array style.
  sum = 0;
  for ( int i = 0; i < len; i++ )
    sum += a[ i ];

  printf( "%d\n", sum );

  // Or, with a pointer.

  // Pre-compute where we want to stop.
  int *end = a + len;

  // Now, iterate from the start up to but not including end.
  // This used to give you some performance improvement.
  sum = 0;
  for ( int *p = a; p < end; p++ )
    sum += *p;

  printf( "%d\n", sum );

  // Or, we can work our way backward, then we don't need
  // the end pointer.
  sum = 0;
  for ( int *p = a + len - 1; p >= a; p-- )
    sum += *p;

  printf( "%d\n", sum );

  // Try out our two string length methods.
  char str[] = "abcdefg";
  printf( "%d\n", stringLen1( str ) );
  printf( "%d\n", stringLen2( str ) );

  return 0;
}

// Compute the length of a string using plain-old array syntax.
int stringLen1( char const *str )
{
  // Keep moving ahead until we hit the null.
  int i = 0;
  // We could simplify this condition.
  while ( str[ i ] != '\0' )
    i++;

  return i;
}

// Compute the length of a string using pointers and pointer arithmetic.
int stringLen2( char const *str )
{
  // Start at the first character.
  char const * p = str;
  // Here, we're using the fact that the null terminator evaluates to false.
  while ( *p )
    p++;

  // Use pointer arithmetic to see how far ahead we got.
  return p - str;
}
