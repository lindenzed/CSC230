/**
    This program defines the functions in the pgm
    header file.  The functions are then used by the
    images modifiers to validate input.
    @file pgm.c
    @author Zach Giles (zgiles)
  */

#include "pgm.h"
#include <stdlib.h>
#include <stdio.h>

//defines magic numbers/characters for header validation
#define HEADER_CHAR 'P'
#define HEADER_INT 2

/**
Checks for leading whitespace on a line
@return the first character that isn't whitespace
*/
char checkLeadingWhitespace() {
    char c;
    scanf("%c", &c);
    while (c == ' ' || c == '\n') {
        scanf("%c", &c);
    }
    return c;
}

/**
Checks the header type and exits with a 255 status if there is an error
*/
void checkType() {
    char pgmChar;
    int pgmInt;
    if (scanf("%c%d", &pgmChar, &pgmInt) == 2 && pgmInt == HEADER_INT && pgmChar == HEADER_CHAR) {
        if (scanf("%c", &pgmChar) == 1) {
            if (pgmChar == '\n') {
                return;//success if only P2 is present on line
            }
            if (pgmChar == ' ') { //checks for whitespace after P2
                while (pgmChar == ' ') {
                    scanf("%c", &pgmChar);
                }
                if (pgmChar == '\n') {
                    return;//success if only P2 is present on line with whitespace after
                }
            }
        }
        exit(BAD_HEADER); //exits if there are other characters on the first line besides P2
    }
    exit(BAD_HEADER);
}

/**
Skips a line of input used for comments
*/
void skipLine() {
    char c;
    while (c != EOF && c != '\n') {
        if (scanf("%c", &c) == EOF) { //sentinal to exit with error if comments are present and EOF is reached before integer is scanned
            exit(BAD_HEADER);
        }
    scanf("%c", &c); //consumes input till EOF of EOL
    }
}

/**
Checks to see if the line begins with the comment hash
@return the first character of the line if it isn't the comment hash
*/
char checkComment() {
    char c = checkLeadingWhitespace();
    while (c == '#') { //checks for comment
        skipLine();
        c = checkLeadingWhitespace();
    }
    return c;
}

/**
Converts the first characters in the header dimensions to ints after being read as characters
@param the character to convert to an int in the dimensions
*/
int convertCharToInt(char c) {
    if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || 
        c == '7' || c == '8' || c == '9' ) {
        int x = c - '0'; //convert to integer
        int dimension;
        char spaceCheck = ' ';
        char newLineCheck = '\n';
        char whitespaceCheck;
        scanf("%c", &whitespaceCheck);
        if (whitespaceCheck == newLineCheck || whitespaceCheck == spaceCheck) {
         return (c - '0');
         }
        //if the integer for the dimension is greater than 9
        if (scanf("%d", &dimension) == 1) {
            x = x * 10; //move the inital integer to the left wrt to the decimal
            
            //if the integer for the dimension is only two digits long the resulting integer scan will only be 0-9
            if (dimension >= 0 && dimension <= 9) {
                return x + dimension; //return the two digit dimension
            }
            int temp = dimension;
            while (temp / 10 != 0) { //if the integer for the dimension is three or more digits
                x = x *10; // move the initial integer to the left wrt to the decimal 
                temp = temp / 10;
            }
            return x + dimension; //return the three or more digit dimension
        }
        return x; //if dimension is only one digit return the one digit dimension
    }
    exit(BAD_HEADER);
}

/**
Converts the character values read as the maximum intensity to an integer
@param c character to convert to int
@return in the range value
*/
int convertCharToIntRange(char c) {
    if (c == '2') {
        int x = c - '0'; //convert to integer
        int dimension;
        if (scanf("%d", &dimension) == 1) {
            x = x * 10; //move the inital integer to the left wrt to the decimal
            //if the integer for the dimension is only two digits long the resulting integer scan will only be 0-9
            if (dimension >= 0 && dimension <= 9) {
                return x + dimension; //return the two digit dimension
            }
            int temp = dimension;
            while (temp / 10 != 0) { //if the integer for the dimension is three or more digits
                x = x *10; // move the initial integer to the left wrt to the decimal 
                temp = temp / 10;
            }
            return x + dimension; //return the three or more digit dimension
        }
        return x; //if dimension is only one digit return the one digit dimension
    }
    exit(BAD_HEADER);
}

/**
Reads a dimension as an integer
@return the integer dimension
*/
int readDimension() {
    int sum = 0;
    if (scanf("%d", &sum) != 1) {
        exit(BAD_HEADER);
    }
    //char c = checkComment(); //returns the first character not on a line that begins with '#'
    /*while (c != ' ' || c != '\n') {
        sum = sum + (c - '0');
        scanf("%c", &c);
        if (c == ' ' || c == '\n'){
            return sum;
        }
        else {
            sum = sum * 10;
        }
    }*/
    return sum;
}

/**
Checks the range to see if it is valid if not exits with status 255
*/
void checkRange() {
    char c = checkComment();
    int range = convertCharToIntRange(c);
    if (range != STD_RANGE) { //if the range entered is not the standard range exit program with bad header error
        exit(BAD_HEADER);
    }
    return;
}

/**
Reads the pixels and writes them to a unsigned char array
@param height height of the image
@param width the width of the image
@param pix the character array to store the values in
*/
void readPixels( int height, int width, unsigned char pix[ height ][ width ] ) {
    int i;
    int j;
    int temp;
    for (i = 0; i < height; i++) {
        for (j =0; j < width; j++) {
            if (scanf("%d", &temp) != 1){
                exit(BAD_PIXEL);
            }
            if (temp < 0) {
                exit(BAD_PIXEL);
            }
            if (temp > STD_RANGE) {
                exit(BAD_PIXEL);
            }
            pix[i][j] = (unsigned char) (temp);
        }
    }
}

/**
Writes the image to a character array with a maximum line count of 70
@param height height of the array
@param width width of the array
@param pix the array to write to the file
*/
void writeImage(int height, int width, unsigned char pix[ height ][ width ] ) {
    int counter = 0; //counter for 70 char requirement
    int tokenCounter = 0;
    int i;
    int j;
    int values = height * width;
    if(width > height){
        for (i = 0; i < width; i++) {
            for (j = 0; j < height; j++) {
                int thisCounter = 0;
                int nextCounter = 0;
                int thisDigit =  (int)pix[i][j];
                int thisTemp = (int)pix[i][j];
                int nextTemp = (int)pix[i][j + 1];
                tokenCounter++;
                while (thisTemp / 10 != 0) {
                    thisCounter++;
                    thisTemp = thisTemp / 10;
                }
                thisCounter++;//for number missed in inital division
                while (nextTemp / 10 != 0) {
                    nextCounter++;
                    nextTemp = nextTemp / 10;
                }
                nextCounter++;//for number missed in initial division
                nextCounter++;//for added space needed if number is added
                if (counter < 70) {
                    if (counter + thisCounter <= 70) {
                        if (counter + thisCounter + nextCounter <= 70) {
                            if (values == tokenCounter) {
                                printf("%d\n", thisDigit);
                                return;
                            }
                            printf("%d ", thisDigit);
                            counter = counter + thisCounter + 1;
                        }
                        else {
                            printf("%d\n", thisDigit);
                            counter = 0;
                        }
                    }
                    else {
                        printf("%c", '\n');
                        counter = 0;
                    }
                }
                else {
                    printf("%c", '\n');
                    counter = 0;
                }
            }
        }
    }
    if(height >= width){
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                int thisCounter = 0;
                int nextCounter = 0;
                int thisDigit =  (int)pix[i][j];
                int thisTemp = (int)pix[i][j];
                int nextTemp = (int)pix[i][j + 1];
                tokenCounter++;
                while (thisTemp / 10 != 0) {
                    thisCounter++;
                    thisTemp = thisTemp / 10;
                }
                thisCounter++;//for number missed in inital division
                while (nextTemp / 10 != 0) {
                    nextCounter++;
                    nextTemp = nextTemp / 10;
                }
                nextCounter++;//for number missed in initial division
                nextCounter++;//for added space needed if number is added
                if (counter < 70) {
                    if (counter + thisCounter <= 70) {
                        if (counter + thisCounter + nextCounter <= 70) {
                            if (values == tokenCounter) {
                                printf("%d\n", thisDigit);
                                return;
                            }
                            printf("%d ", thisDigit);
                            counter = counter + thisCounter + 1;
                        }
                        else {
                            printf("%d\n", thisDigit);
                            counter = 0;
                        }
                    }
                    else {
                        printf("%c", '\n');
                        counter = 0;
                    }
                }
                else {
                    printf("%c", '\n');
                    counter = 0;
                }
            }
        }
    }
}