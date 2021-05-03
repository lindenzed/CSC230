// Same prime-detection strategy, but without any structured
// looping constructs.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Report a list of prime values.
 */
int main( void )
{
    // Get the range of values we're supposed to test.
    unsigned int low, high;
    if ( scanf( "%d%d", &low, &high ) != 2 ) {
        printf( "Invalid input\n" );
        exit( EXIT_FAILURE );
    }
  
  // Write your own, ugly solution, using goto instead of structured looping.
    unsigned int fact = 2;
    unsigned int v = low;
    topOfRangeLoop:
    if(v <= high) {
        topOfPrimeLoop:
        if (fact * fact <= v) {
            if (v % fact == 0) {
                v++;
                fact = 2;
                goto topOfRangeLoop;
            }
            else {
                fact++;
                goto topOfPrimeLoop;
            }
        }
        else {
            printf("%u\n", v);  
            v++;
            fact = 2;
            goto topOfRangeLoop;
        }
    }


  
  return EXIT_SUCCESS;
}
