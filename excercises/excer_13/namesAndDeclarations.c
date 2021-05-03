// Demonstration of declaring struct instances along with the
// struct definition.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// You can define a struct and start making instances at the same time.
struct Grade {
  double minimum;
  char letter;
} aGrade = { 90.0, 'A' };

// You can even define an anonymous struct, if you never need to use
// it again.
struct {
  double latitude;
  double longitude;
} raleigh = { 35.7806, 78.6389 };

int main()
{
  // Nothing to do in main.
  // All the interesting code is in the declarations above.

  return 0;
}
