// A first example of macros that take parameters.

#include <stdio.h>

// Print double whatever's in a
#define P2(a) printf("%d\n", (a)+(a))

int main(void) {

   int x = 10;
   P2(x);

   return 0;

}
