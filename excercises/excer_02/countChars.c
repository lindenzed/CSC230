/**
   Sample program to read and count all the characters on standard input.
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
  int ccount = 0;

  // Keep reading until we hit the EOF.
  int ch;
  while ( ( ch = getchar() ) != EOF )
    ccount++;

  // Report how many characters we found.
  printf( "%d\n", ccount );
  
  // Better than just returning zero.
  return EXIT_SUCCESS;
}
