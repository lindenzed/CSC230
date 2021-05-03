// Demonstration of structs.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // For strcpy();

// Define a new type of struct,
// this usually goes at file scope
// (outside any function).
struct Person {
  char name[ 12 ];
  double height;
  int age;
};

int main()
{
  // Make some uninitialized person instances.
  struct Person p1;

  // p1 has its own name, height and age fields.  We can access
  // them with the dot operator (just like in Java)
  p1.height = 1.75;
  p1.age = 24;

#ifdef NEVER
  // But, this won't work.  We can't assign arrays like this
  // (really, this will try to assign char pointers, but we can't use p1.name
  // as a destination of an assignment like this.)
  p1.name = "Mary";
#endif

  // To assign the name, we could do it ourselves, one char at a time.
  // This is kind of a silly way to copy a string, but it will work.
  {
    int i = 0;
    do {
      p1.name[ i ] = "Mary"[ i ];
    } while ( p1.name[ i++ ] );
  }

  // Really, this would have been better.  There's a C standard library
  // function to copy strings for you, but we haven't covered it yet.
  strcpy( p1.name, "Elizabeth" );

  // Then, we can access the contents of the fields, using the same dot notation.
  printf( "%s : %.2f meters : %d years\n", p1.name, p1.height, p1.age );
    
  // We can initialize a struct's fields when we declare it.
  // Values of the fields in the same order they were declared.
  struct Person p2 = { "William", 1.85, 27 };

  printf( "%s : %.2f meters : %d years\n", p2.name, p2.height, p2.age );

  // Or using the C99 syntax, we can explicitly say which fields we're
  // initializing.
  struct Person p3 = { .age = 33, .name = "Agatha", .height = 1.7 };
  printf( "%s : %.2f meters : %d years\n", p3.name, p3.height, p3.age );

  return 0;
}
