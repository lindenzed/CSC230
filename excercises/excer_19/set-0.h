/** An abstract object for a set of integer values. */

#ifndef _SET_H_
#define _SET_H_

#include <stdbool.h>

/** Initialize the set to an empty set. */
void makeSet();

/** Insert the given value into the set, or do nothing if it's already
    in the set. */
void insertValue( int val );

/** Return true if the given value is in the set. */
bool containsValue( int val );

/** Free anything allocated by the set. */
void destroySet();

#endif
