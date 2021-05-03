/**
	@file arithmetic.c
	@author Zach Giles (zgiles)
	A program that sums numbers 1 to 1000000000
*/
// Include the stdio header, so you can call printf().  I'll use a comment
// like the following to show where you're expected to add code.

#include <stdio.h>

// Write the start of the main function.

int main()
{
	long sum = 0;
	int counter = 1;
	while(counter <= 1000000000) {
		sum += counter;
		counter++;
	}

  // Declare a variable, sum, with type long (so it will have enough
  // capacity), and initialize it to zero.

  // see above
  
  // Use a loop to add up all the integers from 1 to 1000000000 storing the
  // total in the variable, sum.

  // see above

  // I've written the next line of the code for you, since we haven't
  // yet gone over how to print out numbers.  This prints out a
  // long value stored in the variable sum.

  printf( "%c", *("zyxwvu" + 2) );

  // Return with successful exit status.
	return 0;
}
