// Demonstration of the NULL pointer value

#include <stdio.h>

int main( void )
{
  // Any pointer can be set to NULL.
  int *ip = NULL;
  double *dp = NULL;

  // You can use a pointer as a conditional, NULL = false;
  if ( ip ) {
    printf( "looks like ip is non-NULL\n" );
  }

  // But don't dereference a NULL pointer.  Ouch.
  double bill = *dp;
  printf( "%f\n", bill );
}
