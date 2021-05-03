// Showing off basic array operations and initialization syntax

#include <stdio.h>
#include <stdbool.h>

int main( void )
{
  // Make an array with 20 elements.
  int a[ 20 ];

  // Put something in element 5.
  a[ 5 ] = 75;

  // Print it out.
  printf( "a[ 5 ] = %d\n", a[ 5 ] );

  // And backward, to show we can.
  printf( "5[ a ] = %d\n", 5[ a ] );

  // I wonder what's in the elements we haven't initialized.
  printf( "What's in a[]: " );
  for ( int i = 0; i < 20; i++ )
    printf( "%d ", a[ i ] );
  printf( "\n" );

  // This block is here so the list variable will go out of scope
  // and I can use it for something else later.
  {
    // We can give an array an initial value when we declare it.
    int list[ 10 ] = { 1, 2, 3, 10, 20, 30, 100, 200, 300 };

    // We can use sizeof() to figure out the number of array elements.
    printf( "This list takes %zd bytes of memory,\n", sizeof( list ) );
    printf( "so it has %zd elements.\n", sizeof( list ) / sizeof( int ) );
    
    // We didn't provide enough initializers above.  Remaining elements will
    // be initialized to zero.  See:
    printf( "What's in list[]: " );
    for ( int i = 0; i < sizeof( list ) / sizeof( list[ 0 ] ); i++ )
      printf( "%d ", list[ i ] );
    printf( "\n" );
  }

  {
    // We can let the compiler figure out how long the array needs to be.
    int list[] = { 1, 2, 3, 10, 20, 30, 100, 200, 300 };
    
    // Now, we just have 9 elements.
    printf( "What's in list[]: " );
    for ( int i = 0; i < 9; i++ )
      printf( "%d ", list[ i ] );
    printf( "\n" );
  }

  {
    // Alternative initialization syntax.
    int list[] = { [1] = 2, [3] = 10, [5] = 30, [2] = 45 };
    
    // Now, we just just 6 elements, the ones we didn't specify get
    // initialized to 0.
    printf( "What's in list[]: " );
    for ( int i = 0; i < 6; i++ )
      printf( "%d ", list[ i ] );
    printf( "\n" );
  }

  {
    // We can even jump around, and initialize consecutive
    // elements together.
    int list[] = { [5] = 30, 100, 200, [1] = 2, [3] = 10, 20 };
    
    // Now, we just 8 elements, since element 7 was the highest one to get a value.
    printf( "What's in list[]: " );
    for ( int i = 0; i < 8; i++ )
      printf( "%d ", list[ i ] );
    printf( "\n" );
  }
}
