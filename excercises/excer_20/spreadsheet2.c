// Demonstration of how we could do regular-old member functions
// (methods) in C, with the illusion that derived classes inherit the
// function.  Really, we already did the hard work for this when we
// wrote the previous version of the program.

// This version adds a member function to the base class, getWidth(),
// to return the value of the width field, so client code doesn't have
// to directly access the field.  Since derived classes have the same
// memory layout for this field, they can access the field using the
// same function..  All the code from the previous version is here,
// but I've reduced the commenting a little.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/************************************************************************
 * Base class, Cell, just holds a field for the width of the cell.
 ************************************************************************/
typedef struct {
  // Width of the cell.
  int width;
} Cell;

// Make a new Cell.
Cell *makeCell( int width )
{
  // Allocate a Cell and fill in its fields (just one)
  Cell *this = (Cell *)malloc( sizeof( Cell ) );
  this->width = width;
  return this;
}

// Here's the member function.  It only uses the fields that are part
// of Cell, so any object that starts with the same memory structure
// can use this function.
int getWidth( Cell *this )
{
  return this->width;
}

/************************************************************************
 * Derived class, Money, adds a monetary value.
 ************************************************************************/
typedef struct {
  // Field "inherited" from Cell
  int width;

  // A new field for storing a monetory value.
  int val;
} Money;

// Make a new Money object.
Money *makeMoney( int width, int val )
{
  // Allocate a Money object and fill in its fields
  Money *this = (Money *)malloc( sizeof( Money ) );
  this->width = width;
  this->val = val;
  return this;
}

/**********************************************************************/

// Print a horizontal ceparator between between rows of output.
void printSeparator( Cell *row[], int len )
{
  for ( int i = 0; i < 3; i++ ) {
    printf( "+" );
    // As in main, this is like calling a method on each cell.
    for ( int j = 0; j < getWidth( row[ i ] ); j++ )
      printf( "-" );
  }
  printf( "+\n" );
}

int main()
{
  // A grid of cells in our spreadsheet.
  Cell *sheet[ 2 ][ 3 ];

  // Fill in the cells with different objects.
  sheet[ 0 ][ 0 ] = makeCell( 10 );
  sheet[ 0 ][ 1 ] = (Cell *) makeMoney( 12, 375 );
  sheet[ 0 ][ 2 ] = makeCell( 16 );

  sheet[ 1 ][ 0 ] = makeCell( 10 );
  sheet[ 1 ][ 1 ] = (Cell *) makeMoney( 12, 890 );
  sheet[ 1 ][ 2 ] = makeCell( 16 );

  // Print out an outline for the cells.
  for ( int i = 0; i < 2; i++ ) {
    printSeparator( sheet[ i ], 3 );
    for ( int j = 0; j < 3; j++ ) {
      // Here, we're calling the member function rather than accessing
      // the width field directly.  As before, this works because the
      // Cell part of every object has the same memory layout, even
      // though cells point to different types of objects.
      Cell  *c = sheet[ i ][ j ];
      printf( "|%*s", getWidth( c ), "" );
    }
    printf( "|\n" );
  }
  printSeparator( sheet[ 1 ], 3 );
  

  // Free memory for every cell object.
  for ( int i = 0; i < 2; i++ ) {
    for ( int j = 0; j < 3; j++ ) {
      free( sheet[ i ][ j ] );
    }
  }
  
  return 0;
}
