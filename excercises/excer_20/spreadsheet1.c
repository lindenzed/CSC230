// Demonstration of a technique for inheritance in C.  Internally,
// this is sort of how languages like C++ and Java provide inheritance
// and function overriding.

// There are more sophisticated ways to do this, better for larger
// projects, but this is not a bad approach for a first look at object
// orientation in C.

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

// Like a constructor for a Cell.  Dynamically allocate it, fill in
// its field and return a pointer to a new Cell object.
Cell *makeCell( int width )
{
  // Allocate a Cell and fill in its fields (just one)
  Cell *this = (Cell *)malloc( sizeof( Cell ) );
  this->width = width;
  return this;
}

/************************************************************************
 * Derived class (subclass), Money keeps all the same fields as Cell
 * (in the same layout).  It adds a field for storign a monetary value
 * in the memory after the fields inherited from the base class.
 ************************************************************************/
typedef struct {
  // Field "inherited" from Cell
  int width;

  // A new field for storing a monetory value.
  int val;
} Money;

// Like a constructor for Money.  Create, initialize and return a pointer
// to a new Money object.
Money *makeMoney( int width, int val )
{
  // Allocate a Money object and fill in its fields
  Money *this = (Money *)malloc( sizeof( Money ) );
  this->width = width;
  this->val = val;
  return this;
}

/**********************************************************************/

// A utilitiy fuction to print a horizontal separator between rows of the
// spreadsheet.
void printSeparator( Cell *row[], int len )
{
  for ( int i = 0; i < 3; i++ ) {
    printf( "+" );
    // As in main, we're getting the width field out of each cell.
    int width = row[ i ]->width;
    for ( int j = 0; j < width; j++ )
      printf( "-" );
  }
  printf( "+\n" );
}

int main()
{
  // A grid of cells in our spreadsheet.
  Cell *sheet[ 2 ][ 3 ];

  // Fill in cells of the spreadsheet.  Notice, we have to cast here
  // for anything that's not a real Cell pointer.  The programming
  // language doesn't really know about the object orientation tricks
  // we're doing. ... It would sure be nice if we had a language that
  // did. ...
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
      // Here, we're just printing space for the conents of each cell.
      // Every cell has a width field, (at the same offset from the
      // start of the struct), so we can access it using the same
      // code, even though some of these point to Cell instances and
      // some point to Money.
      Cell  *c = sheet[ i ][ j ];
      printf( "|%*s", c->width, "" );
    }
    printf( "|\n" );
  }
  printSeparator( sheet[ 1 ], 3 );
  

  // These objects are all dynamically allocated.  We should free
  // their memory.  Good thing free doesn't require us to say how much
  // memory we're freeing, since these objects are really of different
  // sizes.
  for ( int i = 0; i < 2; i++ ) {
    for ( int j = 0; j < 3; j++ ) {
      free( sheet[ i ][ j ] );
    }
  }
  
  return 0;
}
