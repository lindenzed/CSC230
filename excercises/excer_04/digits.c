// Do some I/O and math with unsigned types.

#include <stdlib.h>
#include <stdio.h>

/**
   Add up all the digits in the value, x, and return the sum.
*/
unsigned int digitSum( unsigned long x )
{
  unsigned long sum = 0;
  while ( x / 10 != 0) {
    sum += x % 10;
    x = x / 10;
  }
  sum += x;
  return sum;
}

int main()
{
  // Range of values we're supposed to check.
  unsigned long low, high;

  // Target sum we're supposed to look for.
  unsigned int target;

  // Read the range of values from the user.
  int lowRangeMatch = scanf("%lu", &low);
  int highRangeMatch = scanf("%lu", &high);

  // Read the digit sum we're supposed to look for.
  int targetMatch = scanf("%u", &target);
  if (lowRangeMatch + highRangeMatch + targetMatch != 3) {
    return EXIT_FAILURE;
  }
  if (target == 0 && low == 0) {
    printf("0");
    return EXIT_SUCCESS;
  }
  // Check all values from low up to high (inclusive), and report the ones
  // that have the given digit sum.
  while (low <= high ) {
    if (digitSum(low) == target) {
      printf("%lu\n", low);
    }
    low++;
  }

  return EXIT_SUCCESS;
}
