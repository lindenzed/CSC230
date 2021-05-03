//
// Demonstration of break, continue and goto (the statement that must not be named)
// These let us change the flow of control in ways that aren't reflected in the structure
// of the program (so, they generally hurt readability).  Break and continue are not
// as bad as goto, since they at least act on just the innermost loop.
//
#include <stdio.h>
#include <stdbool.h>

int main( void )
{
  // A nested loop, with no fancy changes in the flow of control.
  for ( int i = 0; i < 10; i++ ) {
    for ( int j = 0; j < 10; j++ ) {
      printf( "." );
      printf( "*" );
    }
    printf( "\n" );
  }
  
  printf( "-------------------------\n" );

  // A nested loop, with break to exit the innermost loop early.
  for ( int i = 0; i < 10; i++ ) {
    for ( int j = 0; j < 10; j++ ) {
      printf( "." );
      if ( j > i )
        break;
      printf( "*" );
    }
    printf( "\n" );
  }

  printf( "-------------------------\n" );

  // A nested loop, with continue to sometimes skip part of a loop
  // iteration.
  for ( int i = 0; i < 10; i++ ) {
    for ( int j = 0; j < 10; j++ ) {
      printf( "." );
      if ( j > i )
        continue;
      printf( "*" );
    }
    printf( "\n" );
  }

  printf( "-------------------------\n" );

  // A nested loop, with goto to do the job of break.
  for ( int i = 0; i < 10; i++ ) {
    for ( int j = 0; j < 10; j++ ) {
      printf( "." );
      if ( j > i )
        goto done_1;
      printf( "*" );
    }
  done_1:
    printf( "\n" );
  }

  printf( "-------------------------\n" );

  // No structured loops at all.  We can do it all with goto.
  // I don't like to write this code; I sure wouldn't like to read it.
  int i = 0;
 outer_top:
  if ( i >= 10 )
    goto finished;
  int j = 0;
 inner_top:
  if ( j >= 10 )
    goto done_2;
  printf( "." );
  printf( "*" );
  j++;
  goto inner_top;
 done_2:
  printf( "\n" );
  i++;
  goto outer_top;
 finished:


  // The following code is bad, so I've used the preorocessor to
  // omit it.

#ifdef NEVER
  // You can even jump inside a loop, but should you?
  goto inside;

  for ( int k = 1; k < 10; k++ ) {
  inside:
    // I wonder what value k will have. The compiler will
    // probably warn you about this.
    printf( "%d\n", k );
  }
#endif

  return 0;
}
