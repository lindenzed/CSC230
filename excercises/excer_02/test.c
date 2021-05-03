#include <stdio.h>
#include <stdlib.h>

int main( void )
{

int ival = 0;
  float fval = 0;
  int matches = scanf( "%d%f", &ival, &fval );
  printf( "%d %d %f\n", matches, ival, fval );
  return 0;
  }