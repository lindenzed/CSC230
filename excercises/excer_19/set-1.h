n/** A set of integer values, where client code can have as many sets as it wants.
    But this implementation exposes the representation to the client. */

#ifndef _SET_H_
#define _SET_H_

#include <stdbool.h>

/** Node used to represent a value in a set. */
struct Node {
  /** Value in the set. */
  int val;

  /** Pointer to the next node. */
  struct Node *next;
};

/** Representation for a set of values. */
typedef struct {
  /** Representation for each value in the set, as a linked list. */
  struct Node *head;
} Set;

/** Initialize the given structure to an empty set. */
void makeSet( Set *s );

/** Insert the given value into the set, or do nothing if it's already
    in the set. */
void insertValue( Set *s, int val );

/** Return true if the given value is in the set. */
bool containsValue( Set *s, int val );

/** Free the memory for the given set. */
void destroySet( Set *s );

#endif
