// Showing why you need avoid calling a macro
// with a parameter that has side effects.

#include <stdio.h>

#define MAX(a,b) ((a)>(b) ? (a) : (b))

int main()
{
   int x;
   int y = 2;
   int z = 3;

   // Here, it looks like y and z just get evaluated once,
   // But, in the expanded macro ...
   x = MAX(y++, z++);

   printf("%d %d %d\n", x, y, z);

   return 0;
}
