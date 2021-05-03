/** A generic abstract data type for a set of of any type of value you
    want, but you have to help by providing some extra parameters to
    work with that value. */

#ifndef _SET_H_
#define _SET_H_

#include <stdbool.h>
#include <stdlib.h>

/** type name for the set. */
typedef struct SetStruct Set;

/** make a new set of values, each one of the given size, using the given
    comparison function to decide if two values are identical. */
Set *makeSet( size_t vsize, bool (*same)( void const *v1, void const *v2 ) );

/** Insert the given value into the set, or do nothing if it's already
    in the set. */
void insertValue( Set *s, void const *val );

/** Return true if the given value is in the set. */
bool containsValue( Set *s, void const *val );

/** Free the memory for the given set. */
void destroySet( Set *s );

#endif
