// Code to read numbers from standard input inserting them into a list
// in sorted order as we read them.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node for building our linked list.
struct NodeStruct {
  // Value in this node.
  int value;

  // Pointer to the next node.
  struct NodeStruct *next;
};

// A short type name to use for a node.
typedef struct NodeStruct Node;

/*
  Create a node for the given value and insert it into the given list
  in the proper location to keep the list sorted.  Return an updated
  head pointer.  The head should only need to change if this value gets
  inserted at the front of the list.  Otherwise, you can just return
  the old head pointer.
*/
Node *insert( Node *head, int val )
{
  Node *newNode = (Node *)malloc(sizeof(Node));//allocate space for the new node
  newNode-> value = val;
  newNode->next = NULL;

  //Don't need this leaving in the program to remind me why you do it this way to elimnate code
  	/*if (head == NULL ) {
		head = newNode;
		return head;
	}
	if (newNode->value < head->value ) {
		newNode->next = head;
		head = newNode;
		return head;
	}*/


  Node **target = &head;//set node to head
  while ( *target && (newNode->value) > (*target)->value  ) { //traverses loops
  	target = &(*target)->next;
  }
  newNode->next = (*target);//set the new node next position to what the next position of target 
  (*target) = newNode;//reset targets next to the new node
  return head;

}

int main()
{
  // Pointer to the head node.
  Node *head = NULL;

  // Read a list of numbers from building a sorted list as we
  // read them.
  int x;
  while ( scanf( "%d", &x ) == 1 ){
    // Insert the new value, and get back the (possibly updated) head pointer.
    head = insert( head, x );
  }

  // Print out the list.
  for ( Node *n = head; n; n = n->next ) {
  	printf("%d ", n->value);
  }
  printf("\n");
  
  // Free all the nodes.
  while (head) {
  	Node *next = head->next;
  	free(head);
  	head = next;
  }
  return 0;
}
