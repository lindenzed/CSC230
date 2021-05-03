#include "set-3.h"
#include <string.h> // for memcpy

/** Node used to represent a value in a set. */
struct Node {
  /** Pointer to a value in the set (there are more efficient ways to do this). */
  void *val;

  /** Pointer to the next node. */
  struct Node *next;
};

/** Representation for a set of values (there's a typedef in the header) */
struct SetStruct {
  /** Size of each value in the set. */
  size_t vsize;

  /** Function to compare two of the values supported by the set. */
  bool (*same)( void const *v1, void const *v2 );

  /** Representation for each value in the set, as a linked list. */
  struct Node *head;
};

Set *makeSet( size_t vsize, bool (*same)( void const *v1, void const *v2 ) )
{
  // Allocate a set representation, and make it empty.
  Set *s = (Set *) malloc( sizeof( Set ) ) ;
  s->head = NULL;
  
  // Remember details about the value type we're working with.
  s->vsize = vsize;
  s->same = same;
  
  return s;
}

void insertValue( Set *s, void const *val )
{
  // See if the value's there already.
  for ( struct Node *n = s->head; n; n = n->next )
    if ( s->same( n->val, val ) )
      return;

  // It's not in the list.  Make a node for the new value.
  struct Node *n = (struct Node *) malloc( sizeof( struct Node ) );

  // Copy over the given value.
  n->val = malloc( s->vsize );
  memcpy( n->val, val, s->vsize );

  // Link the new node in at the front.
  n->next = s->head;
  s->head = n;
}

bool containsValue( Set *s, void const *val )
{
  // Look for the given value in the list.
  for ( struct Node *n = s->head; n; n = n->next )
    if ( s->same( n->val, val ) )
      return true;

  // Return false if we don't find it.
  return false;
}

void destroySet( Set *s )
{
  // Free all the nodes in the set.
  while ( s->head ) {
    struct Node *n = s->head;
    s->head = s->head->next;

    free( n->val );
    free( n );
  }
  
  // Free the set itself.
  free( s );
}
