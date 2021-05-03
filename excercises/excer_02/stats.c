/*
   Read a sequence of real numbers and report the minimum, maximum
   and average values.
 */
#include <stdio.h>
#include <stdlib.h>

int main( void )
{
  // Figure out how many values there are.
  int n;
  scanf("%d", &n);
  int count = n;

  // Read in the first value into val.
  double val;
  scanf("%lf", &val);
  count--;

  // That first value is our tentative min and max value.
  double minValue = val, maxValue = val, total = val;

  // Get the remaining n-1 values and update minValue, maxValue and total
  // based on each one.
  while (count  > 0) {
    count--;
    scanf("%lf", &val);
    total += val;
    if (val < minValue) {
        minValue = val;
    }
    else if (val > maxValue) {
        maxValue = val;
    }
  }

  // Report the stats.
  printf("Minimum: %8.2lf\n", minValue);
  printf("Maximum: %8.2lf\n", maxValue);
  printf("Average: %8.2lf\n", total / n);

  // Exit successfully.
  system("pause");
  return 0;
}
