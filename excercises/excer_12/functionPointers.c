// Showing how to declare and use function pointers.
// Give this program some command-line arguments to get it
// to do somethng interesting.

#include <stdio.h>

// Our own string length function.
int stringLength( char *str )
{
  // Keep moving ahead until we hit a null
  char *p = str;
  while ( *p )
    p++;
  
  // Return the pointer difference.
  return p - str;
}

// Like stringLength, but just count vowels.
int countVowels( char *p )
{
  // Notice, we're changing our only copy of 
  // the pointer to this string.  That's OK,
  // we only need to go through the string once.
  
  int vc = 0;
  while ( *p ) {
    // Ugly, but effective.
    if ( *p == 'a' || *p == 'A' ||
         *p == 'e' || *p == 'E' ||
         *p == 'i' || *p == 'I' ||
         *p == 'o' || *p == 'O' ||
         *p == 'u' || *p == 'U' )
      vc++;
    p++;
  }
  
  return vc;
}

// Call f on every function in the given string list.  Total up and return
// all the values f returns.
int applyFunction( char **strings, int stringCount, int (*f)( char * ) )
{
  int total = 0;
  for ( int i = 0; i < stringCount; i++ ) {
    total += f( strings[ i ] );
  }

  return total;
}

int main( int argc, char *argv[] )
{
  // I can hold a pointer to a function that takes a char array and returns
  // an int.
  int (*f)( char * );

  // Set f to point to a particular function, just the length function.
  f = stringLength;

  // Call this function on each command-line parameter.
  for ( int i = 0; i < argc; i++ ) {
    // Given a function pointer, f, you call it just like a regular function.
    int result = f( argv[ i ] );
    printf( "%d\n", result );
  }

  // Of course, the point of a function pointer is you can call
  // a function even if you don't know the particular function you're calling.
  int total;
  
  // Add up all the characters in this list.
  total = applyFunction( argv, argc, stringLength );
  printf( "Total chars: %d\n", total );

  // Now, get the same funciton to total just the vowels
  total = applyFunction( argv, argc, countVowels );
  printf( "Total vowels: %d\n", total );
}
