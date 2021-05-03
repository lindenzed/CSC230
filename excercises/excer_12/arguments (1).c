// Finally, we can make sense of the command-line arguments to a C program.

#include <stdio.h>

// Two parameters, number of arguments and an array of pointers to each one.
int main( int argc, char *argv[] )
{
  // Report how many command line argumetns you got.
  printf( "Called with %d arguments\n", argc );

  // Report the command line arguments themselves.
  for ( int i = 0; i < argc; i++ )
    printf( "    %s\n", argv[ i ] );
}
