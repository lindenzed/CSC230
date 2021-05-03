// Demonstration of how pointers let us try to read/write any memory
// location.

#include <stdio.h>

int main()
{
  // Make up an address
  int *p = (int *)12345678;

  // I wonder if I can successfully write to this
  // memory location.  Let's find out.
  *p = 100;

  // We probably won't get past the previous line during execution.
  // But, if we do. ...

  // Let left-over stack conents be our address.
  int *q;

  // Then try to write to there.
  *q = 250;

  return 0;
}
