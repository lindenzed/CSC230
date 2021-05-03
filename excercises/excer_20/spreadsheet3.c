// Demonstration of overriding a function. In C++, this would be
// called a virtual function, a function that can be implemented
// differently for each of its derived classes.  The base class now
// contains a pointer to a function to use for printing.  Derived
// classes can plug in their own value for this field to get
// class-specific behavior.

// Like the previous examples, there are more sophisticated ways to do
// this, but, hopefully, this one will be easy to understand.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/************************************************************************
 * Base class, Cell, now with a width field and a pointer to a function for
 * printing cells.
 ************************************************************************/
typedef struct CellTag {
  // Pointer to a function to use for printing a cell.
  void (*print)( struct CellTag * );

  // Width of the cell.
  int width;
} Cell;

// Actual function used to print the base class.  Every instance of Cell will
// carry aorund a pointer to this function.
void printCell( Cell *this ) {
  // Just print an empty cell of the right width.
  printf( "%*s", this->width, "" );
}

// Make a new Cell.
Cell *makeCell( int width )
{
  // Allocate a Cell and fill in its fields, the width and the pointer ot its print
  // function.
  Cell *this = (Cell *)malloc( sizeof( Cell ) );

  // Fill in the pointer to our print function.
  this->print = printCell;

  this->width = width;
  return this;
}

// Member function of Cell to return the width field.
int getWidth( Cell *this )
{
  return this->width;
}

/************************************************************************
 * Derived class (subclass), Money keeps all the same fields as Cell
 * (in the same layout).  It adds a field for storign a monetary value
 * in the memory after the fields inherited from the base class.
 ************************************************************************/
typedef struct {
  // Fields "inherited" from Cell, with the same layout in memory.
  void (*print)( Cell * );
  int width;

  // A monetory value to display
  int val;
} Money;

// Actual function used to print the Money class.  Every instance of
// Money will carry around a pointer to this function in its print
// field.
void printMoney( Cell *cell ) {
  // If this function gets called, the parameter must really be a pointer to 
  // a Money object.  Let's cast it to the more specific type.
  Money *this = (Money *)cell;
  
  // Print the contents of this cell, as money (would be nice to add a $)
  printf( "%*d.%02d", this->width - 3, this->val / 100, this->val % 100 );
}

// Make a new Money object.
Money *makeMoney( int width, int val )
{
  // Allocate a Money object and fill in its fields
  Money *this = (Money *)malloc( sizeof( Money ) );

  // Fill in the pointer to our print function.
  this->print = printMoney;

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

  // Fill in cells with some object pointers.
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
      printf( "|" );

      // Get the current element of the spreadsheet (this is really just to
      // simplify the syntax of the next line).
      Cell *c = sheet[ i ][ j ];

      // Call its print function, passing in the object it's supposed to print.
      c->print( c );
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
