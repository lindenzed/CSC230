// Demonstration of returning pointers from functions, good and bad.

#include <stdio.h>

// Return the address of the largest value in the given array.
// We're assuming the array is non-empty.
int *findLargest( int a[], int len )
{
  int largest = 0;
  for ( int i = 1; i < len; i++ )
    if ( a[ i ] > a[ largest ] )
      largest = i;

  // Return the address of the largest item.
  return &( a[ largest ] );
}

// But this here is a bad idea.  We're returning
// the address of a local stack variable, one that
// won't technically exist as soon as the function
// returns.
int *addNumbers( int a[], int len )
{
  int sum = 0;
  for ( int i = 0; i < len; i++ )
    sum += a[ i ];

  // Here's the mistake.  The compiler gives me a warning about this.
  return &sum;
}

int main()
{
  // A list of values to play with.
  int list[] = { 20, 45, -10, 18, 3, 24, 16 };

  // Get the largest item.
  int *p = findLargest( list, sizeof( list ) / sizeof( list[ 0 ] ) );
  
  // We can print it out.
  printf( "Largest: %d\n", *p );

  // We can even change it via the pointer.
  *p += 1;
  
  // This will give us a pointer to memory that may be immediately
  // reused for something else.
  int *sp = addNumbers( list, sizeof( list ) / sizeof( list[ 0 ] ) );

  // I may get lucky and that memory might still contain the same thing
  // when I dereference sp.
  printf( "Sum: %d\n", *sp );

  // But, who knows after I've let some other function (e.g., printf) start
  // using stack memory (I didn't actually see this happen on the
  // common platform.  Really, even the previous call to printf might have
  // reported the wrong value)
  printf( "Again: %d\n", *sp );

  return 0;
}
