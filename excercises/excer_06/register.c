// Test to see if we get any performance improvement using a CPU register.
#include <stdio.h>

int main( void )
{
  // Run our test a few times.
  for ( int loops = 0; loops < 10; loops++ ) {

    // This will overflow, but it doesn't matter.
    int total = 0;
    for ( register int i = 0; i < 1000000000; i++ )
      total += i;

  }

  // Nothing to print, we just care about the runtime.
}
