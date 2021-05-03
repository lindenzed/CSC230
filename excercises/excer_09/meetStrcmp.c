// Demonstration of string comparison functions.  We haven't really
// learned how to make arrays of strings yet.  When we do, we'll be
// able to do more interesting things with string functions.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  // Space for a 99-character string.
  char word[ 100 ];

  // Read a word from the user.
  printf( "Enter a word: " );
  scanf( "%99s", word );

  // See if they entered the word, "blue".
  if ( strcmp( word, "blue" ) == 0 ) {
    printf( "You entered the word \"blue\"\n" );
  } else {
    printf( "You didn't enter the word \"blue\"\n" );
  }

  // Use strcmp to check lexicographic (i.e., dictionary) order.
  if ( strcmp( word, "zebra" ) < 0 ) {
    printf( "That word goes before \"zebra\" in the dictionary.\n" );
  } else {
    printf( "That word doesn't go before \"zebra\" in the dictionary.\n" );
  }

  return 0;
}
