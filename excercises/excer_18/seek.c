// Showing off rewind(), fseek() and ftell().

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )
{
  FILE *fp = fopen( "output.txt", "w" );

  // Write the alphabet to file.
  fprintf( fp, "----efghijklmnopqrstuvwxyz\n" );

  // Oops, I got the firt few characters wrong.  Let's go back and
  // fix them.
  rewind( fp );
  fprintf( fp, "abc" );

  // Remember our position (for later)
  long dPos = ftell( fp );

  // Go to the end, and put another copy of the alphabet, this time in all caps.
  fseek( fp, 0, SEEK_END );
  fprintf( fp, "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n" );

  // Oops, I forgot to fix the d character near the start of the whole file.
  // fortunately, we remembered where to go back to.
  fseek( fp, dPos, SEEK_SET );
  fputc( 'd', fp );

  fclose( fp );

  return 0;
}
