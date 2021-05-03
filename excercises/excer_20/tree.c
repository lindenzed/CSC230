// A (potentially unbalanced) tree implemented in C, using
// pointer-to-pointer to simplify insertion.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node for building trees.
struct NodeTag {
  // Value in this node.
  int value;

  // Pointer to the left and right subtrees.
  struct NodeTag *left, *right;
};

// A short type name to use for a node.
typedef struct NodeTag Node;

// Struct containing the whole tree
typedef struct {
  // Root of the tree.
  Node *root;
} Tree;

// Inser the given value into the tree.
bool insert( Tree *tree, int val )
{
  // Place where this value may go.
  Node **spot = &tree->root;

  // Walk down to the null pointer where we
  // may insert this value.
  while ( *spot ) {
    // Is it already in the tree?
    if ( (*spot)->value == val )
      return false;

    // Go into left or right subtree.
    if ( val < (*spot)->value )
      spot = &(*spot)->left;
    else
      spot = &(*spot)->right;
  }

  // Make a new node with this value.
  Node *n = (Node *)malloc( sizeof( Node ) );
  n->value = val;
  n->left = n->right = NULL;

  // Make this pointer poit to it.
  *spot = n;
  return true;
}

// Recursive traversal to print the values in the tree.
void printValues( Node *n )
{
  if ( n ) {
    // Inorder traversal, print the left subtree
    printValues( n->left );
    // Then the value at this node
    printf( "%d ", n->value );
    // Then the right subtree.
    printValues( n->right );
  }
}

// Print the tree, using indentation to show the structure.
void printTree( Node *n, int depth )
{
  if ( n ) {
    // We print the subtrees backward here, so you can lean
    // your head to the left and read the left (bottom) to right (top)
    // structure of the tree.
    // Then the value at this node, indented
    printTree( n->right, depth + 1 );
    for ( int i = 0; i < depth; i++ )
      printf( "  " );
    printf( "%d\n", n->value );
    printTree( n->left, depth + 1 );
  }
}

int main()
{
  // Make a tree.  Again, something like a constructor would be better.
  Tree tree = { NULL };

  // Add a few values to the tree.
  insert( &tree, 21 );
  insert( &tree, 50 );
  insert( &tree, 75 );
  insert( &tree, 18 );
  insert( &tree, 42 );
  insert( &tree, 9 );
  insert( &tree, 103 );

  // Print out the values in sorted order.  This requires a traversal.
  printValues( tree.root );
  printf( "\n\n" );
  
  // Print out the shape of the tree (well, sort of)
  printTree( tree.root, 0 );
  
  return 0;
}
