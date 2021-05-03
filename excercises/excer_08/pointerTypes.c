// Demonstration of warnings when we assign between incompatible
// pointer types.

#include <stdio.h>

int main( void )
{
  // Make some values of different types.
  char c = 'a';
  float f = 1.23;
  short s = 123;

  // Each type has its own pointer type.
  char *cp = &c;
  float *fp = &f;
  short *sp = &s;

  // Converting values, the compiler can handle.
  c = f;
  f = s;
  s = c;

  // But, converting pointer types, the compiler will
  // warn you about.
  fp = &c;
  sp = &f;
  cp = &s;

  // A cast of pointer type will tell the compiler to
  // quit complaining
  fp = (float *) &c;
  sp = (short *) &f;
  cp = (char *) &s;

  // You can cast values
  f = (float) *cp;
  
  // but, really, you don't need to
  f = *cp;
}
