// Demonstration of value semantics for structs and reference semantics
// via pointer-to-struct.  Also, some bad examples.

#include <stdio.h>

// A record of a scheduled event.
struct Event {
  char name[ 10 ];
  int hour;
  int minute;
};

// Take an event by value (a copy) and print out its
// contents.
void printEvent_v( struct Event e )
{
  printf( "%s %d:%02d\n", e.name, e.hour, e.minute );
}

// Same functionality, but with pass-by-reference via a pointer
// to a struct.
void printEvent_r( struct Event const *e )
{
  printf( "%s %d:%02d\n", (*e).name, (*e).hour, (*e).minute );
}

// A function to read an event from the user and return a copy of it (by value)
struct Event readEvent_v()
{
  struct Event e;

  printf( "Event Name: " );
  scanf( "%s", e.name );  // look out, could buffer overflow.

  printf( "Time: " );
  scanf( "%d:%d", &e.hour, &e.minute );

  return e;
}

// A function to read an event and write it into the given struct object.
void readEvent_r( struct Event *e )
{
  printf( "Event Name: " );
  // Here, we're using the -> operator, that's better.
  scanf( "%s", e->name );

  printf( "Time: " );
  scanf( "%d:%d", &e->hour, &e->minute );
}

// A bad way to try to return a struct.
struct Event *readEvent_bad1()
{
  struct Event e;

  printf( "Event Name: " );
  scanf( "%s", e.name );

  printf( "Time: " );
  scanf( "%d:%d", &e.hour, &e.minute );

  // Bad idea, returning the address of a variable that's about to
  // go away.  The compiler will probably warn us about this.
  return &e;
}

// This won't crash or anything, but it's useless.  If we
// change e, we're just changing a copy of the struct that's
// passed in.
void readEvent_bad2( struct Event e )
{
  printf( "Event Name: " );
  scanf( "%s", e.name );

  printf( "Time: " );
  scanf( "%d:%d", &e.hour, &e.minute );
}

int main()
{
  // Make a couple of structs
  struct Event e1 = { "Wake Up", 6, 30 };
  struct Event e2;

  // We get a deep copy of the structs when we assign them.
  e2 = e1;

#ifdef NEVER
  // But you can't compare with ==
  if ( e2 == e1 )
    printf( "They're the same!\n" );
#endif

  // This give us some choice when we call a funciton.
  
  // We can pass a struct by value:
  printEvent_v( e1 );

  // Or, we can use a pointer to pass by reference.
  // This could be a lot less expensive.  Most programmers
  printEvent_r( &e1 );

  // Parse an event and get it back as a return value.
  // This is what we were talking about when we described returning
  // a struct as a way of returning multiple values.
  e2 = readEvent_v();
  printEvent_r( &e2 );

  // Another option, read in an eveent and fill in the provided struct that's
  // passed by reference.
  readEvent_r( &e2 );
  printEvent_r( &e2 );

  // Two techniques that won't work.

  // First, try to get the address of a returned struct.  This could work, but
  // not the way the funciton is doing it.
  struct Event *e3 = readEvent_bad1();
  printEvent_r( e3 );
  

  // A different problem, here the function is just changing its copy of our struct.
  readEvent_bad2( e2 );
  printEvent_r( &e2 );
  
  return 0;
}
