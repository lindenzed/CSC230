// Linked list, without a global variable for the head.  Here, instead
// of storing the list as just a node pointer, we have a little struct
// representing the list.  This is more like how we would do things in
// an object oriented language, with all the state for a data structure
// wrapped up in an object.

// It also makes the pass-by-reference syntax for modifying the list
// easier to think about, since we're passing in a pointer to a list
// structure, rather than just a pointer to the head pointer.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node for building our linked list.
struct NodeTag {
  // Value in this node.
  int value;

  // Pointer to the next node.
  struct NodeTag *next;
};

// A short type name to use for a node.
typedef struct NodeTag Node;

// Struct containing the whole list.
typedef struct {
  // Head pointer
  Node *head;
} List;

// Add a value to the start of the list.
// Here, we just pass the List struct by reference.
void addValue( List *list, int val )
{
  // Make a new node.
  Node *n = (Node *)malloc( sizeof( Node ) );

  // Save val in the value field.
  n->value = val;

  // Link it to the start of the list.
  n->next = list->head;
  list->head = n;
}

// Here, we go find the given value and remove it.
bool removeValue1( List *list, int val )
{
  // This is a typical way of doing things, treating
  // the first node as a special case.
  if ( list->head && list->head->value == val ) {
    // Unlink the head node.
    Node *n = list->head;
    list->head = list->head->next;

    // Free it and tell the caller we removed this value.
    free( n );
    return true;
  }

  // If the value isn't the first, try to find its
  // predecessor node.
  Node *pred = list->head;
  while ( pred->next && pred->next->value != val )
    pred = pred->next;

  // Did we stop before the end?
  if ( pred->next ) {
    // Unlink the node after pred.
    Node *n = pred->next;
    pred->next = pred->next->next;

    // Free it and tell the caller we removed this value.
    free( n );
    return true;
  }

  // I guess we didn't find the value.
  return false;
}

// Same here, but we use pointer-to-pointer.  We don't have
// to treat the first node as a special case.
bool removeValue2( List *list, int val )
{
  // target is the address of the pointer we need to change.
  Node **target = &list->head;
  while ( *target && (*target)->value != val )
    // Get the pointer inside the next node.
    target = &(*target)->next;

  // Did we stop before the end?
  if ( *target ) {
    // Unlink the node after target.
    Node *n = (*target);
    *target = (*target)->next;

    // Free it and tell the caller we removed this value.
    free( n );
    return true;
  }

  // I guess we didn't find the value.
  return false;
}

int main()
{
  // Now, my list is an instance of List.
  // We don't have a constructor, so we have to initialize
  // it ourselves.
  List list = { NULL };

  // Add a few values to the list.
  addValue( &list, 21 );
  addValue( &list, 50 );
  addValue( &list, 75 );
  addValue( &list, 18 );
  addValue( &list, 42 );
  addValue( &list, 9 );
  addValue( &list, 103 );

  // Try removing a node, using the traditional technique
  removeValue1( &list, 42 );
  // and using pointer-to-pointer
  removeValue1( &list, 103 );

  // Use a for loop to walk down the list, printing out the values.
  for ( Node *n = list.head; n; n = n->next )
    printf( "%d ", n->value );
  printf( "\n" );

  // Previous examples have been leaking memory.  Let's try to free
  // the list.
  
#ifdef NEVER
  // Here's how to not do it.  This is a bad idea because
  // we're counting on using the next pointer out of the
  // node we just freed.
  for ( Node *n = list->head; n; n = n->next )
    free( n );
#endif

  // This is better.  We make a copy of the next pointer before we
  // free the node.
  while ( list.head ) {
    // It's like we're repeatedly chopping off the node at the start
    // of the list.  There are other ways to do this.
    Node *next = list.head->next;
    free( list.head );
    list.head = next;
  }
  
  return 0;
}
