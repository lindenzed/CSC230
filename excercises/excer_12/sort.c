#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int intComp( const void *aptr, const void *bptr )
{
  // We're sorting an array of ints, so the pointers will really be pointers
  // to ints.
  int const *a = aptr;
  int const *b = bptr;

  // Compare the values these pointers point to.
  if ( *a < *b )
    return -1;
  if ( *a > *b )
    return 1;
  return 0;
}

int stringComp( const void *aptr, const void *bptr )
{
  // We're sorting an array of char arrays, so the pointers will really be pointers
  // to char arrays.
  char const (*a)[ 20 ] = aptr;
  char const (*b)[ 20 ] = bptr;

  // Compare the values these pointers point to.
  return strcmp( *a, *b );
}

int ptrComp( const void *aptr, const void *bptr )
{
  // We're sorting an array of char pointers, so the pointers will really be pointers
  // to char pointers
  char * const *a = aptr;
  char * const *b = bptr;

  // Compare the values these pointers point to.
  return strcmp( *a, *b );
}

int main()
{
  {
    // Make an array of numbers.
    int list[] = {
      25,
      10,
      19,
      32,
      7
    };

    qsort( list, 5, sizeof( list[ 0 ] ), intComp );
    
    for ( int i = 0; i < 5; i++ )
      printf( "%d\n", list[ i ] );
    printf( "\n" );
  }
  
  {
    // Try an array of arrays.
    char list[][ 20 ] = {
      "turnip",
      "broccoli",
      "kale",
      "cabbage",
      "rhubarb"
    };

    qsort( list, 5, sizeof( list[ 0 ] ), stringComp );
    
    for ( int i = 0; i < 5; i++ )
      printf( "%s\n", list[ i ] );
    printf( "\n" );
  }
  
  {
    // Try an array of pointers.
    char *list[] = {
      "turnip",
      "broccoli",
      "kale",
      "cabbage",
      "rhubarb"
    };

    qsort( list, 5, sizeof( list[ 0 ] ), ptrComp );
    
    for ( int i = 0; i < 5; i++ )
      printf( "%s\n", list[ i ] );
    printf( "\n" );
  }
}
