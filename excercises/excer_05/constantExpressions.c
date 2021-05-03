//
// Demonstration of some constant expressions.  These are required for the 
// labels on a swtich, and in some other, probably more common places we
// haven't learned about yet.
//
#include <stdio.h>
#include <stdbool.h>

int main( void )
{
  int val;
  printf( "Enter a value: " );
  scanf( "%d", &val );

  int three = 3;
  
  switch ( val ) {
    
  case 0: // A trivial constant expression.
    printf( "It's a zero\n" );
    break;

  case 2 / 2: // A slightly more interesting one.
    printf( "It's a one\n" );
    break;

  case 25 / 7 % 2 + 19 - 6 * 3: // More complex
    printf( "It's a two\n" );
    break;

#ifdef NEVER
  case three: // But this wouldn't work.
    printf( "It's a three\n" );
    break;
#endif

  default:
    printf( "It's some other value.\n" );
  }

  // This line is just to keep the compiler from
  // complaining that I never use the variable, three.
  three++;

  return 0;
}
