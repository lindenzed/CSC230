/*
 * Showing evidence of sign extension, what happens at the bit level when
 * negative values get converted to a wider type.
 */

#include <stdio.h>
#include <stdbool.h>

int main()
{
  // Some small variables to play with.
  unsigned char x;
  signed char y;

  x = 0xA9;  // binary 10101001 (that means 169)
  y = 0xA9;  // binary 10101001 (here, that's -87)

  // But, notice, these two variables get printed
  // differently.
  printf( "%x\n", x );
  printf( "%x\n", y );

  // It's not the printing that's doing this.  It's the conversion to
  // unsigned vs signed int.
  // In the case of y (signed char), we're seeing sign extension.

  return 0;
}
