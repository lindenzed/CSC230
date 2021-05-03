// Demonstration that macros can do things regular
// functions can't

#include <stdio.h>

#define SWAP(a, b, type) \
{ \
   type temp = a; \
   a = b; \
   b = temp; \
}


int main(void)
{
   int x = 5;
   int y = 7;
   printf("x=%d y=%d\n", x, y);
   SWAP(x, y, int);
   printf("x=%d y=%d\n", x, y);

   return 0;
}   
