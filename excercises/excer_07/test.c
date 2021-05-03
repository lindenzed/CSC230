#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main () {
  int a = 5;
  int *b = &a;
  int c = *b;
  int *d = &c;

  *b += *d;
  printf( "%d\n", a );

}