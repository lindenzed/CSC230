/**
  @file stringval.h
  @author Zach Giles

  Support for values that contain strings.
*/
#include "value.h"


/** Make a sublcass of value representing the given
String value passed as a pointer to a character array.
The String value is dynamically allocated along with 
the char* inside the String sturct that holds the value.
@param *val the pointer to the character array
@return Value pointer to the dynamically allocated value string
*/
Value *makeString( char *val );

