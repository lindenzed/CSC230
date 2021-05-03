// Showing how you can use void pointers.

#include <stdio.h>

int main( int argc, char *argv[] )
{
#ifdef NEVER
  // You can't do this.
  void v;
#endif

  // But you can make a void pointer.
  void *vp;

  // What can you do with it?  It can hold
  // the value of any other pointer, without
  // even needing a cast.

  // A float, no problem.
  float f = 3.14;
  vp = &f;

  // A long, easy.
  long l = 123456789;
  vp = &l;

  // But, you can't dereference the void pointer
  // directly
#ifdef NEVER
  printf( "%ld\n", *vp );
#endif

  // But, you can assign or cast the void pointer back
  // to a more specific type if you want to use what
  // it points to.
  // You don't even need a cast
  long *lp = vp;
  printf( "%ld\n", *lp );

  // But, a cast is still a good idea, especially if you
  // want your code to be compatible with C++.
  lp = (long *)vp;
  printf( "%ld\n", *lp );
}
