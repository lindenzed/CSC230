#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

int main()
{

  int list_cap = 5; 
  int list_len = 0; 
  double *list = ( double * )malloc( list_cap * sizeof( double ) );

  double val;
  while ( scanf( "%lf", &val ) == 1 ) {

    if( list_len >= list_cap) { 
    list_cap *= 2; 
    list = ( double * )realloc( list, list_cap * sizeof( double) ); };


    list[ list_len ] = val;
    list_len += 1;
  }


  for(int i = 0; i < list_len; i++)
    for(int j = 0; j < list_len - i - 1; j++)
      if ( list[ j ] > list[ j + 1 ] ){
        double tmp = list[ j ]; 
        list[ j ] = list[ j + 1 ]; 
        list[ j + 1 ] = tmp;}


  for(int i = 0; i < list_len; i++)
    printf( "%.2f\n", list[ i ] );

  return 0;
}