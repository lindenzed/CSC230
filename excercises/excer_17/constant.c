// A demonstration of a preprocessor macro for a named constant.
// Nothing fancy.

#include <stdio.h>

#define PI 3.1415926

int main(void)
{
   double d;
   printf("Enter the diameter: ");
   scanf("%lf", &d);
   double x = PI * d;
   printf("Circumference: %.2f\n", x);
   return 0;
}
