#include "stringval.h"
#include "syntax.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Representation for a String, a subclass of Value.*/
typedef struct {
  void (*print)( Value *value, FILE *stream );
  bool (*equals)( Value *value, Value *other );
  Value *(*copy)( Value *value );
  void (*destroy)( Value *value );

  /**String value contained in this Value sublcass. */
  char *stringVal;
}String;

/**implementation of print for String*/
static void printString( Value *value, FILE *stream )
{
  String *this = (String *) value;
  fprintf(stream, "%s", this->stringVal );
}

/** Implementation of copy for String */
static Value *copyString( Value *value )
{
  return makeString( ((String *) value)->stringVal );
}

/**Implementation of equals for String*/
static bool equalsString( Value *value, Value *other )
{
  String *this = (String *) value;
  if ( other-> copy != copyString ) {
    return false;
  }
  String *that = (String *) other;
  if (strcmp( this->stringVal, that->stringVal ) != 0 ) {
    return false;
  }
  return true;
}


/** Implementation of destroy for String */
static void destroyString( Value *value )
{
  String *this = (String *) value;
  free( this->stringVal);
  free( this );
}

Value *makeString( char *val )
{
  // Allocate space for an String object.
  String *this = (String *) malloc( sizeof( String ) );
  //Allocate space for the Strings value
  this->stringVal = (char *)malloc( sizeof( char ) * strlen( val ) + 1 );
  strcpy( this->stringVal, val );
  // Record pointers to the right functions for working with this object.
  this->print = printString;
  this->equals = equalsString;
  this->copy = copyString;
  this->destroy = destroyString;

  return (Value *) this;
}
