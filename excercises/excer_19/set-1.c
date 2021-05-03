#include "set-1.h"
#include <stdlib.h>

void makeSet( Set *s )
{
  // Start with an empty set.
  s->head = NULL;
}

void insertValue( Set *s, int val )
{
  // See if the value's there already.
  for ( struct Node *n = s->head; n; n = n->next )
    if ( n->val == val )
      return;

  // It's not.  Add this value to the front.
  struct Node *n = (struct Node *) malloc( sizeof( struct Node ) );
  *n = (struct Node) { val, s->head };
  s->head = n;
}

bool containsValue( Set *s, int val )
{
  // Look for the given value in the list.
  for ( struct Node *n = s->head; n; n = n->next )
    if ( n->val == val )
      return true;

  // Return false if we don't find it.
  return false;
}

void destroySet( Set *s )
{
  // As long as the set is non-empty, free the node at the front.
  while ( s->head ) {
    struct Node *n = s->head;
    s->head = s->head->next;
    free( n );
  }
}
