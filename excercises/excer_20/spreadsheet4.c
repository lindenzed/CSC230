// Adding another derived class of Cell, containing some dynamically
// allocated memory.  This requires a virtual function for freeing the
// memory.

// Like the previous examples, there are more sophisticated ways to do
// this, but, hopefully, this one will be easy to understand.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/************************************************************************
 * Base class, Cell, now with two pointer to functions.
 ************************************************************************/
typedef struct CellTag {
  // Pointer to a function to use for printing a cell.
  void (*print)( struct CellTag * );

  // Pointer to a function to use for freeing the memory of a cell.
  void (*destroy)( struct CellTag * );

  // Width of the cell.
  int width;
} Cell;

// Function to print a Cell
void printCell( Cell *this ) {
  // Just print an empty cell of the right width.
  printf( "%*s", this->width, "" );
}

// Function to free a Cell.
void destroyCell( Cell *this ) {
  free( this );
}

// Make a new Cell.
Cell *makeCell( int width )
{
  // Allocate a Cell and fill in its fields, the width and the pointer ot its print
  // function.
  Cell *this = (Cell *)malloc( sizeof( Cell ) );

  // Fill in pointers to our functions.
  this->print = printCell;
  this->destroy = destroyCell;

  this->width = width;
  return this;
}

// Member function of Cell to return the width field.
int getWidth( Cell *this )
{
  return this->width;
}

/************************************************************************
 * Derived class, Money, adds a monetary value.
 ************************************************************************/
typedef struct {
  // Fields "inherited" from Cell, with the same layout in memory.
  void (*print)( Cell * );
  void (*destroy)( Cell * );
  int width;

  // A monetory value to display
  int val;
} Money;

// Function used to print a Money value.
void printMoney( Cell *cell ) {
  // Get Cell as a more specific type.
  Money *this = (Money *)cell;
  
  // Print the contents of this cell, as money (would be nice to add a $)
  printf( "%*d.%02d", this->width - 3, this->val / 100, this->val % 100 );
}

// Function to free a Money object
void destroyMoney( Cell *this ) {
  free( this );
}

// Make a new Money object.
Money *makeMoney( int width, int val )
{
  // Allocate a Circle and fill in its fields
  Money *this = (Money *)malloc( sizeof( Money ) );

  // Fill in the pointers to our functions.
  this->print = printMoney;
  this->destroy = destroyMoney;

  this->width = width;
  this->val = val;
  return this;
}

/************************************************************************
 * Derived class, Text, stores an arbitrary string.
 ************************************************************************/
typedef struct {
  // Fields "inherited" from Cell, with the same layout in memory.
  void (*print)( Cell * );
  void (*destroy)( Cell * );
  int width;

  // A copy of a string given at creation time.
  char *str;
} Text;

// Function used to print a Text value.
void printText( Cell *cell ) {
  // Get Cell as a more specific type.
  Text *this = (Text *)cell;
  
  // Print the contents of this cell
  printf( "%*s", this->width, this->str );
}

// Function to free a Text object
void destroyText( Cell *cell ) {
  // Get Cell as a more specific type.
  Text *this = (Text *)cell;

  // Free the string we contain.
  free( this->str );

  // Then free the memory for the Text struct itself.
  free( this );
}

// Make a new Text object, keeping a copy of the give string.
Text *makeText( int width, char const *str )
{
  // Allocate a Text object and fill in its fields
  Text *this = (Text *)malloc( sizeof( Text ) );

  // Fill in the pointers to our functions.
  this->print = printText;
  this->destroy = destroyText;

  this->width = width;

  // Copy the string passed in to us.
  this->str = (char *)malloc( strlen( str ) + 1 );
  strcpy( this->str, str );

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
  sheet[ 0 ][ 2 ] = (Cell *) makeText( 16, "Gum" );

  sheet[ 1 ][ 0 ] = makeCell( 10 );
  sheet[ 1 ][ 1 ] = (Cell *) makeMoney( 12, 890 );
  sheet[ 1 ][ 2 ] = (Cell *) makeText( 16, "Sandwich" );

  // Print out an outline for the cells.
  for ( int i = 0; i < 2; i++ ) {
    printSeparator( sheet[ i ], 3 );
    for ( int j = 0; j < 3; j++ ) {
      printf( "|" );

      // Call this cell's function to print itself.
      Cell *c = sheet[ i ][ j ];
      c->print( c );
    }
    printf( "|\n" );
  }
  printSeparator( sheet[ 1 ], 3 );

  // Ask all the cells to free themselves.
  for ( int i = 0; i < 2; i++ ) {
    for ( int j = 0; j < 3; j++ ) {
      // Call this cell's function to free itself.
      Cell *c = sheet[ i ][ j ];
      c->destroy( c );
    }
  }
  
  return 0;
}
