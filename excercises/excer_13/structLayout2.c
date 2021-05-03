// Demonstration of how structures are laid out in memory, possibly with
// some padding between the fields.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// A struct with a better layout for its fields.
struct Person {
  char name[ 12 ];
  int age;
  double height;
};

int main()
{
  // With a new layout, this particular struct doesn't need any padding.
  printf( "sizeof( struct Person) = %zd\n", sizeof( struct Person ) );

  // It's introducing some padding,  I wonder if we can see where it is.
  struct Person bill;

  // Print the starting addresses of bill's fields.
  printf( "name:   %p\n", &bill.name );
  printf( "age:    %p\n", &bill.age );
  printf( "height: %p\n", &bill.height );

  return 0;
}
