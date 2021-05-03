/** Without something like a finally block, it's easy to leak
    resources. */
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

/** Read a sequence of integers from the given file, store them
    in list, and return the number of values read. */
int readValues( int *list, int capacity, FILE *fp, jmp_buf *eenv )
{
  int vcount = 0;
  int m, v;

  // Keep read values as long as its successful.
  while ( ( m = fscanf( fp, "%d", &v ) ) == 1 ) {
    // Did we exceed capacity.
    if ( vcount >= capacity )
      longjmp( *eenv, 1 );
    
    list[ vcount++ ] = v;
  }

  // Did we hit something that wasn't a number?
  if ( m != EOF )
    longjmp( *eenv, 1 );

  // OK, we reached the end of the input.
  return vcount;
}

/** A function in the middle, a place where we could leak some resources. */
void middleFunction( jmp_buf *eenv )
{
  // Open an input file.
  FILE *fp = fopen( "input.txt", "r" );
  if ( !fp )
    longjmp( *eenv, 1 );
  
  int capacity = 100;
  int *list = (int *)malloc( capacity * sizeof( int ) );
  
  int vcount = readValues( list, capacity, fp, eenv );

  // Print out the values backward.
  for ( int i = vcount - 1; i >= 0; i-- )
    printf( "%d\n", list[ i ] );

  // Free resources (this doesn't get done if we jump past this function).
  fclose( fp );
  free( list );
}

void topFunction()
{
  jmp_buf eenv;

  // Remember this spot in execution.
  if ( setjmp( eenv ) == 0 ) {
    // No error (yet)
    middleFunction( &eenv );
  } else {
    // Longjmp must have jumped back to the setjmp() call.
    printf( "Invalid input!\n" );
  }
}

int main()
{
  topFunction();
  return EXIT_SUCCESS;
}
