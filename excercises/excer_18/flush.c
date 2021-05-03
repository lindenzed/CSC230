// Demonstration of fflush() for pushing output out to stdout.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Unix specific, sorry.

int main( int argc, char *argv[] )
{
  printf( "You can't see me " );
  sleep( 5 );
  printf( "... until you write a newline\n" );

  sleep( 5 );

  printf( "But flushing writes output immediately" );
  fflush( stdout );
  sleep( 5 );

  printf( "... even without a newline.\n" );


  return 0;
}
