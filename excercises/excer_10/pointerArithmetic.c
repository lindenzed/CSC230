// Demonstrating pointer arithmetic.

#include <stdio.h>


int main()
{
  // Some objects to point to.
  char ca[ 10 ];
  int ia[ 10 ];
  double da[ 10 ];

  // Get a pointer to the start of each one.
  char *cp = ca;
  int *ip = ia;
  double *dp = da;

  // Print the values of each pointer.
  printf( "%p %p %p\n", cp, ip, dp );

  // Print each pointer plus one.
  printf( "%p %p %p\n", cp + 1, ip + 1, dp + 1 );

  return 0;
}
