#include "value.h"
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Value Subclasses

/** Representation for an Integer, a subclass of Value. */
typedef struct {
  void (*print)( Value *value, FILE *stream );
  bool (*equals)( Value *value, Value *other );
  Value *(*copy)( Value *value );
  void (*destroy)( Value *value );

  /** Integer value contained in this Value subclass. */
  int val;
} Integer;

/** Implementation of print for Integer */
static void printInteger( Value *value, FILE *stream )
{
  // If this function gets called, value must really be an Integer.
  Integer *this = (Integer *) value;
  fprintf( stream, "%d", this->val );
}

/** Implementation of equals for Integer */
static bool equalsInteger( Value *value, Value *other )
{
  // If this function gets called, value must really be an Integer.
  Integer *this = (Integer *) value;
  
  // If they're not the same type, then theyre not equal. We can use
  // one of the function poitners to make sure other is an Integer.  It is
  // if it has the right print function for an int.
  if ( other->print != printInteger )
    return false;

  // If they're both integers, return true if they contain the same value.
  Integer *that = (Integer *) other;
  return this->val == that->val;
}

/** Implementation of copy for Integer */
static Value *copyInteger( Value *value )
{
  return makeInteger( ((Integer *) value)->val );
}

/** Implementation of destroy for Integer */
static void destroyInteger( Value *value )
{
  free( value );
}

Value *makeInteger( int val )
{
  // Allocate space for an Integer object.
  Integer *this = (Integer *) malloc( sizeof( Integer ) );

  // Record pointers to the right functions for working with this object.
  this->print = printInteger;
  this->equals = equalsInteger;
  this->copy = copyInteger;
  this->destroy = destroyInteger;

  // Record a copy of the given integer value.
  this->val = val;

  return (Value *) this;
}

/** Documented in the header. */
int toInt( Value *value )
{
  // We can use one of the function poitners to make sure this is an
  // Integer.
  if ( value->print != printInteger ) {
    fprintf( stderr, "Expected Integer value\n" );
    exit( EXIT_FAILURE );
  }

  // Get a copy of the value, then free the value that contained it.
  int val = ((Integer *) value)->val;
  value->destroy( value );

  // Return the int value that was inside.
  return val;
}

//////////////////////////////////////////////////////////////////////
// Environment.

// Define your own Environment struct to hold the values of all
// variables.
struct EnvironmentStruct {
  Value **variables;
  char **variableNames;
  int capacity;
  int len;
};
//typedef struct EnvironmentStruct Environment;

/**Allocates memory for an environment and sets the intial capacity and length
@return a pointer to an environment used to hold values*/
Environment *makeEnvironment()
{
  Environment *enviro = (Environment *)malloc( sizeof( Environment ) );
  enviro->capacity = INITIAL_CAPACITY;
  enviro->len = 0;
  enviro->variables = (Value **)malloc( enviro->capacity * sizeof( Value * ) );
  enviro->variableNames = (char **)malloc( enviro->capacity * sizeof ( char * ) );
  return enviro;
}

Value *lookupVariable( Environment *env, char const *name )
{
  for ( int i = 0; i < env->len; i++ ) {
    if ( strcmp( ( env->variableNames[ i ] ), name) == 0 ) {
      return ( ( env->variables[ i ] ) );
    }
  }
  return NULL;
}

void setVariable( Environment *env, char const *name, Value *value )
{
  if ( lookupVariable( env, name ) ) {
    for (int i = 0; i < env->len; i++ ) {
      if (strcmp( ( env->variableNames[ i ] ), name ) == 0) {
        free( env->variables[ i ] );
        env->variables[ i ] = value;
        return;
      }
    }
}
  if ( env->len >= env->capacity ) {
    env->capacity *= DOUBLE_CAPACITY;
    env->variables = realloc( env->variables, sizeof( Value * ) * env->capacity );
    env->variableNames = realloc( env->variableNames, sizeof( char *) * env->capacity );
  }
  env->variables[ env->len ] = value;
  env->variableNames[ env->len ] = (char *)malloc(strlen( name ) );
  strcpy( env->variableNames[ env->len ], name);
  env->len++;
}

void freeEnvironment( Environment *env )
{
  for (int i = 0; i < env->len; i++ ) {
    ( env->variables[ i ] )->destroy(env->variables[ i ] );
    free( env->variableNames[ i ] );
  }
  free( env->variables );
  free (env->variableNames );
  free( env );
}

