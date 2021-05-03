/**This header file includes the operations used to encrypt
and decrypt text

@file operations.h
@author Zach Giles (zgiles)*/

#include <stdlib.h>
#include <stdio.h>
 
/*This function will swap lines m and n
@param m line to swap
@param n other line to swap
*/
void swapLines( int m, int n );

/**This function will shift letters to the left or right
depending on the sign of the integer passed (negative is left).
The magnitude of the value passed will determine how many letters
to shift along the left or right of the alphabet.  For instance
if the letter A is shifted 1 it will become B, and if A is shifted
-1 it will become Z.
@param n the number of letters to shift each letter*/
void shiftLetters( int n );

/**This function will reverse the letters along a line
the first letter becomes the last letter etc*/
void reverseLines();

/**This function will rotate the letters on the line to the left.
The first letter becomes the last letter, the last letter becomes the next to last, etc*/
void rotateLinesLeft();

/**This function will rotate the letters on the line to the right.
The first letter becomes the second letter, the last letter becomes the first letter, etc*/
void rotateLinesRight();