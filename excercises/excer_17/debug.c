// Demonstration of using preprocessor for debugging with conditional compilation.
// and the # notation to get the name of a parameter.

#include <stdio.h>

// Conditional compilation based on the debug flag.
#if defined(DEBUG)
// Print out the value of X, with its name, this macro
// expansion is specific to the int type.
#define REPORT_I( X ) printf( "%s = %d\n", #X, (X) )
#else
// Define macro to do nothing.
#define REPORT_I( X ) 
#endif

int main(void)
{
  // Add up a bunch of values.
  int total = 0;
  for ( int i = 0; i < 20; i++ ) {
    total += i;

    // Optional debugging output.
    REPORT_I( i );
    REPORT_I( total );
  }
  printf( "Total: %d\n", total );
  
  return 0;
}
