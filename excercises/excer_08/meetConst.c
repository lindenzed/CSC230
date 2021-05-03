// Demonstration of the const keyword 

#include <stdio.h>

// We can mark some variables as const.
static int const size = 25;

#ifdef NEVER
// But that doesn't make them real compile-time constatnts.
int arr[ size ];
#endif

void f( int x )
{
  // Most people put the const first.
  const int y = x;

  // You can change x all you want.
  x = 25;

#ifdef NEVER
  // But the const says don't let me change y.
  y = 35;
#endif

  // But still, y's value can vary from call to call.
  printf( "%d\n", y );
}

int main( void )
{
  // Show that y can take different values.
  f( 5 );
  f( 10 );

  // Const gets interesting when you use it with
  // pointers.
  int a = 25;
  int b = 35;
  int c = 45;

  // I can point anywhere, but you can't change the contents of memory
  // I point to.
  int const * x = &a;

  // I stay pointing at b, but you can change it through me.
  int * const y = &b;

  // I stay pointing at c, and you can't change it.
  int const * const z = &c;

#ifdef NEVER
  // Can't change a via this pointer.
  *x = 20;
#endif

  // Of course, you can still change a.  Just not via
  // the x pointer.
  a = 20;

  // But, you can make x point elsewhere.
  x = &b;

#ifdef NEVER
  // But, you cant' change b via x either.
  *x = 30;
#endif

  // Y behaves the other way
  *y = 40;
#ifdef NEVER
  y = &c;
#endif

#ifdef NEVER
  // With z, you can't change either.
  *z = 50;
  z = &a;
#endif

  // But you can still see what it points to.
  printf( "%d\n", *z );
}
