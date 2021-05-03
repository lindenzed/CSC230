// Linked list, without a global variable for the head.  This
// lets us have as many lists as we want, but if we update the
// list in a function, we need some way of getting the updated head
// pointer back to the caller.

// Here, we take the original head pointer as a reference parameter
// (so, a pointer to the head, a pointer to a pointer to a node).

#include <stdio.h>
#include <stdlib.h>

// Node for building our linked list.
struct NodeTag {
  // Value in this node.
  int value;

  // Pointer to the next node.
  struct NodeTag *next;
};

// A short type name to use for a node.
typedef struct NodeTag Node;

// Add a value to the start of the list.
// Here, we thake the had as a pass-by-address parameter.
void addValue( Node **head, int val )
{
  // Make a new node.
  Node *n = (Node *)malloc( sizeof( Node ) );

  // Save val in the value field.
  n->value = val;

  // Link it to the start of the list.
  n->next = *head;
  *head = n;
}

int main()
{
  // Pointer to the head node.
  Node *head = NULL;

  // Add a few values to the list.
  addValue( &head, 75 );
  addValue( &head, 18 );
  addValue( &head, 42 );
  addValue( &head, 9 );
  addValue( &head, 103 );

  // Use a for loop to walk down the list, printing out the values.
  for ( Node *n = head; n; n = n->next )
    printf( "%d ", n->value );
  printf( "\n" );
  
  return 0;
}
