/*
 * Show off passing arrays to functions.
 */
#include <stdio.h>
#include <math.h>

/*
 * Print out the contents of the given table.
 */
void printTable( int table[ 5 ][ 10 ] )
{
  for ( int i = 0; i < 5; i++ ) {
    for ( int j = 0; j < 10; j++ ) {
      printf( "%2d ", table[ i ][ j  ] );
    }
    printf( "\n" );
  }
}

/*
 * Report the number of table rows using the sizeof trick (which
 * won't work here)
 */
void badTableRows( int table[][ 10 ] )
{
  printf( "Table Rows in function: %lu\n", sizeof( table ) / sizeof( table[ 0 ] ) );
}

/*
 * Print table with extra parameters for size.
 */
void smartPrintTable( int rows, int cols, int table[ rows ][ cols ] )
{
  for ( int i = 0; i < rows; i++ ) {
    for ( int j = 0; j < cols; j++ ) {
      printf( "%2d ", table[ i ][ j  ] );
    }
    printf( "\n" );
  }
}

/*
 * A similar idea, but it won't work here, won't even compile.
 */
#ifdef NEVER
void smartPrintTable( int table[ rows ][ cols ], int rows, int cols )
{
  for ( int i = 0; i < rows; i++ ) {
    for ( int j = 0; j < cols; j++ ) {
      printf( "%2d ", table[ i ][ j  ] );
    }
    printf( "\n" );
  }
}
#endif

int main( void )
{
  // Partial initialization, remember what this will do.
  int t1[ 5 ][ 10 ] = {
    { 1, 2, 3 },
    { 4, 5, 6, 7 },
    { 8, 9 },
    { 10 },
  };

  // Same here, but fewer rows.
  int t2[ 4 ][ 10 ] = {
    { 1, 2, 3 },
    { 4, 5, 6, 7 },
    { 8, 9 },
    { 10 },
  };

  // Similar here, but narrower, so the size of each row is different.
  int t3[ 5 ][ 9 ] = {
    { 1, 2, 3 },
    { 4, 5, 6, 7 },
    { 8, 9 },
    { 10 },
  };

  // This will work
  printTable( t1 );
  printf( "\n" );

  // This will work, but it will index out of bounds
  printTable( t2 );
  printf( "\n" );

#ifdef NEVER
  // This won't compile.
  printTable( t3 );
#endif

  // In main, we can tell how big this array is.
  printf( "Table Rows in main: %lu\n", sizeof( t1 ) / sizeof( t1[ 0 ] ) );

  // See, the compiler doesn't really tell the function how big the
  // aray parameter is
  badTableRows( t1 );
  printf( "\n" );

  // Now, this will work.
  smartPrintTable( 4, 10, t2 );
  printf( "\n" );

  // And even this.
  smartPrintTable( 5, 9, t3 );

  return 0;
}
