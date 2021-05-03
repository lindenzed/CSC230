#include <stdio.h>

int main(void) 
{
  // This is safe, there's a null at the end.
  char h[] = "Hello";
  printf( "%s\n", h );

  // Here, it's our responsibility.  Did we put one?  Nope.
  char w[] = {'w','o','r','l','d' };
  // This might print some garbage after the word World, whatever's
  // in memory until we happen to hit a zero.
  printf( "%s\n", w );

  return 0;
}
