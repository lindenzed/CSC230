// Demonstration of accessing external variables.  This file goes with
// stuff.c and stuff.h

#include <stdio.h>
#include "stuff.h"

int main()
{
  // Trying to use x defined in stuff.c
  x++;
  printf( "%d\n", x );
}
