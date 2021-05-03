#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Read words from cin into the given vector of strings.
void readWords( vector< string > &list )
{
	string line;
	while (cin >> line) {
		list.push_back( line );
	}
}

// Use the index operator ( you know, [] ) to print out the list
// of words in reverse.
void printBackward( const vector< string > &list )
{
	cout << "-- Backward --" << endl;

	for ( int i = list.size() - 1; i >= 0; i-- ) {
		cout << list[ i ] << endl;
	}
}

// Use iteratros to print the list forward.
void printForward( const vector< string > &list )
{
	cout << "-- Forward --" << endl;

	vector< string >::iterator p;
	//for( int v : list ) {
	//	cout << v << endl;
	for( auto p = list.begin(); p != list.end(); p++ ) {
		cout << *p << endl;
	}
}

int main()
{
  // You can make a vector of strings.  Why not.
  vector< string > words;

  // Read a list of words.
  readWords( words );

  // Use a template algorithm to sort them.
  sort( words.begin(), words.end() );

  // Print the list backward.
  printBackward( words );

  // Then print it again, forward this time.
  printForward( words );
}
