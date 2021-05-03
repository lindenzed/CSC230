#include "set-0.h"
#include <stdlib.h>

/** Node used to represent a value in a set.  Here in in the implmentation
    file because client code doesn't need to know how we implement the set. */
struct Node {
  /** Value in the set. */
  int val;

  /** Pointer to the next node. */
  struct Node *next;
};

/** Linked list of nodes for values in the set.  Static because other code
    doesn't need to see this. */
static struct Node *head;

void makeSet()
{
  // Start with an empty set.
  head = NULL;
}

void insertValue( int val )
{
  // See if the value's there already.
  for ( struct Node *n = head; n; n = n->next )
    if ( n->val == val )
      return;

  // It's not.  Add this value to the front.
  struct Node *n = (struct Node *) malloc( sizeof( struct Node ) );
  *n = (struct Node) { val, head };
  head = n;
}

bool containsValue( int val )
{
  // Look for the given value in the list.
  for ( struct Node *n = head; n; n = n->next )
    if ( n->val == val )
      return true;

  // Return false if we don't find it.
  return false;
}

void destroySet()
{
  // As long as the set is non-empty, free the node at the front.
  while ( head ) {
    struct Node *n = head;
    head = head->next;
    free( n );
  }
}
