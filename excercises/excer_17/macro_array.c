// Get the preprocessor to write code for you.
#include <stdio.h>

// Make an array filled with 0, 1, 2 ...
#define COUNT_UP(ANAME,SIZE)                    \
  int ANAME[ (SIZE) ];                          \
  {                                             \
    for( int i = 0; i < (SIZE); i++) {          \
      ANAME[i] = i;                             \
    }                                           \
  }                                             \

// Print the contents of the given array.
#define PRINT_I(ANAME)                                          \
  {                                                             \
    for( int i = 0; i < sizeof(ANAME)/sizeof(ANAME[0]); i++) {  \
      printf( "%d\n", ANAME[i] );                               \
    }                                                           \
  }                                                             \
  
int main( void )
{
  COUNT_UP( a, 20 );
  PRINT_I( a );
  return 0;
}
