#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


/** Append a given character, ch, to the end of a resizable array of
    characters.  The representation for the resizable array (str (the
    array), len (number of elements used) and cap (capacity)) are all
    passed by address, so this function can change them if needed. */
void append( char **str, int *len, int *cap, char ch )
{
  // Grow the array if it's not big enough.
  if ( *len + 1 >= *cap ) {
    *cap *= 2;
    *str = (char *) realloc( *str, *cap );
  }

  // Add ch to the end (a little ugly because str, len and cap are
  // all passed by address).
  (*str)[ (*len) ++ ] = ch;
}

char *d_printf( const char *fmt, ... )
{
  // Setup vararg processing
  va_list ap;
  va_start( ap, fmt );

  // Resizable array of chars.
  int len = 0;
  int cap = 5;
  char *dest = (char *) malloc( cap );

  // Go through the format string.
  int pos = 0;
  while ( fmt[ pos ] ) {
    if ( fmt[ pos ] == '%' ) {
      // The current character is a %.  See if it's the start of %s,
      // %u or %% and handle it appropriately if it is.

      if ( fmt[ pos + 1 ] == 's' ) {
        char *stringToAdd = va_arg( ap, char * );
        int i = 0;
        while ( stringToAdd[ i ] ) {
          append( &dest, &len, &cap, stringToAdd[ i++ ]);
        }
      }

      if ( fmt[ pos + 1 ] == 'u' ) {
        unsigned int value = va_arg( ap, unsigned int );
        unsigned int valueCpy = value;
        int counter = 1; //there is a number there
        while ( value / 10 != 0 ) {
          counter++;
          value /= 10;
        }

        int power10 = 1;//To avoid using math.h header
        for (int i = 1; i < counter; i++ ) { //i is one b/c there is a number there
          power10 = power10 * 10;
        }

        for ( int i = 0; i < counter; i++ ) {
          append( &dest, &len, &cap, 48 + valueCpy / power10 % 10);//48 to convert to ANSI code (48 is 0 ANSI)
          power10 /= 10;
        }
      }

      if (fmt[ pos + 1 ] == '%' ) {
        append( &dest, &len, &cap, '%' );
      }

      // Advance past the next two characters in the format string,
      // unless we're at the end of the string already.
      if ( fmt[ pos + 1 ] )
        pos += 2;
      else
        pos += 1;
    } else {
      // Ordinary character, just copy it to the destination string.
      append( &dest, &len, &cap, fmt[ pos ] );
      pos += 1;
    }
  }

  // Null terminate the resulting string.
  append( &dest, &len, &cap, '\0' );
  
  // We're done processing arguments.
  va_end( ap );

  // Return the string we made.
  return dest;
}

// Leave the rest of this unchanged.  This conditional compilation
// code will let me replace main() with a different test function for
// grading.
#ifndef OMIT_MAIN

int main()
{
  char *str;

  // Try a format string with no conversion specifications
  str = d_printf( "Testing\n" );
  printf( "%s", str );
  free( str );

  // A format string with a string conversion specification.
  char *name = "Bill";
  str = d_printf( "Hello %s.\n", name );
  printf( "%s", str );
  free( str );

  // A format string with an unsigned int conversion specification.
  unsigned int val = 72351;
  str = d_printf( "value: %u\n", val );
  printf( "%s", str );
  free( str );

  // A zero might be a special case when you print it.
  val = 0;
  str = d_printf( "A zero looks like \"%u\"\n", val );
  printf( "%s", str );
  free( str );

  // A format string that includes a literal % sign.
  val = 25;
  str = d_printf( "%u%% increase\n", val );
  printf( "%s", str );
  free( str );

  // A format string with a few different conversion specifications.
  str = d_printf( "Countdown: %u 4 %u %s %u 0. %s!\n",
                 5, 3, "2", 1, "blastoff" );
  printf( "%s", str );
  free( str );

  return EXIT_SUCCESS;
}

#endif
