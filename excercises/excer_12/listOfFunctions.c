// Another application of function pointers, a list of
// functions to apply.  Really, this is demonstrating
// the chain-of-responsibility design pattern.

#include <stdio.h>
#include <stdbool.h>

// Default handler for for numbers.
bool nothingSpecial( int val )
{
  printf( "%d is is boring\n", val );
  return true;
}

// See if the number is even.
bool isEven( int val )
{
  if ( val % 2 == 0 ) {
    printf( "%d is even\n", val );
    return true;
  }

  return false;
}

// See if the number is prime
bool isPrime( int val )
{
  for ( int factor = 2; factor * factor <= val; factor++ )
    if ( val % factor == 0 )
      return false;

  printf( "%d is prime\n", val );
  return true;
}

// See if the number is a power of two
bool isPowerOfTwo( int val )
{
  // I just made up this test, but it should work, at least for positive numbers.
  if ( ( val & ( val - 1 ) ) == 0 ) {
    printf( "%d is a power of two\n", val );
    return true;
  }

  return false;
}

// Apply the list of tests in testList to number, until
// one of them returns true.
void testNumber( int number, bool (*testList[])( int ) )
{
  int i = 0;
  while ( ! testList[ i ]( number ) )
    i++;
}

int main( int argc, char *argv[] )
{
  // A list of functions, each able to recognize a type of number.
  bool (*testList[ 10 ])( int );
  int testCount = 0;

  // List of tests to try, in order.  This ends with one
  // that will always return true.
  testList[ testCount++ ] = isPowerOfTwo;
  testList[ testCount++ ] = isPrime;
  testList[ testCount++ ] = isEven;
  testList[ testCount++ ] = nothingSpecial;

  // Try out our tests on some numbers.
  testNumber( 42, testList );
  testNumber( 4096, testList );
  testNumber( 97, testList );
  testNumber( 9, testList );
}
