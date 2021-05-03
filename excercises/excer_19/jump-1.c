/** Demonstration of setjmp/longjmp for error handling. */
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

/** Read a sequence of integers from standard input, and return the sum. */
int readValues( jmp_buf *eenv )
{
  int sum = 0;
  int m, v;

  // Keep read values as long as its successful.
  while ( ( m = scanf( "%d", &v ) ) == 1 )
    sum += v;

  // Did we hit something that wasn't a number?
  if ( m != EOF )
    longjmp( *eenv, 1 );

  // OK, we reached the end of the input.
  return sum;
}

/** A function in the middle, to show that longjmp can jump past this. */
void middleFunction( jmp_buf *eenv )
{
  int sum = readValues( eenv );
  printf( "Sum: %d\n", sum );
}

void topFunction()
{
  jmp_buf eenv;

  // Remember this spot in execution.
  if ( setjmp( eenv ) == 0 ) {
    // If the branch goes this way, then we returned from setjmp for the first
    // time.
    middleFunction( &eenv );
  } else {
    // If the branch goes this way, then we jumped back to setjmp, because of an
    // error.
    printf( "Invalid input!\n" );
  }
}

int main()
{
  topFunction();
  return EXIT_SUCCESS;
}
