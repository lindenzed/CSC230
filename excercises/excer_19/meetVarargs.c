// Demonstration of varargs.

#include <stdio.h>
#include <stdarg.h>

// Takes an intger n, then adds up n subsequent parameters
// and returns the result.
int addIntegers( int n, ... )
{
  // structure for managing variable arguments on the stack.
  va_list ap;

  // Get ready to unpack parameters occurring after n.
  va_start( ap, n );

  int total = 0;
  for ( int i = 0; i < n; i++ )
    // Get the next argument, as an int.
    total += va_arg( ap, int );

  // We're done processing arguments.
  va_end( ap );

  return total;
}

// The funciton needs to be able to figure out how many
// parameters it has, but we don't have to just tell it
// via the first parameter.  This one prints string
// parameters until it hits a NULL pointer.
void printStrings( char *first, ... )
{
  // Setup vararg processing
  va_list ap;
  va_start( ap, first );

  // Print the first string
  printf( "%s\n", first );

  // Keep getting arguments until we hit a null.
  // The assignment inside the conditional looks like
  // a mistake, but it's not.  The extra set of parentheses
  // tells the compiler we did that on purpose
  char *str;
  while ( ( str = va_arg( ap, char * ) ) ) {
    printf( "%s\n", str );
  }

  va_end( ap );
}

// This function is genuinely useful.  It computes the maximum of
// arbitrarily many doubles.  This is only meaningful if we have
// at least one parameter, so the v1 forces the caller to supply
// at least one parameter.  n is still the total number of parameters
// (including v1)
double maximum( int n, double v1, ... )
{
  // Setup vararg processing (after the v1 parameter)
  va_list ap;
  va_start( ap, v1 );

  // Start with v1 as the max.
  double largest = v1;

  // See if any of the other parameters can beat it.
  // Notice, we skip the first parameter.  We already took
  // care of v1, and it's not one of the varargs parameters
  // anyway.
  for ( int i = 1; i < n; i++ ) {
    double v = va_arg( ap, double );
    if ( v > largest )
      largest = v;
  }

  va_end( ap );
  return largest;
}

int main( int argc, char *argv[] )
{
  // Call this funciton.
  int total = addIntegers( 5, 17, 42, 98, 3, 27 );
  printf( "Sum: %d\n", total );

#ifdef NEVER
  // But, it's up to us to use this properly.  Here, we're giving
  // the wrong number of parameters for n.
  total = addIntegers( 29, 17, 42, 98, 3, 27 );
  printf( "Sum: %d\n", total );
#endif

  // Here, the NULL says where the last parmeter is.
  printStrings( "one", "two", "three", "four", NULL );

  // this is kind of nice, an arbitrary-parameter max.
  double max = maximum( 6, 32.1, 15.32, 2.99, 45.2, 13.62, 7.0 );
  printf( "max: %f\n", max );
}

