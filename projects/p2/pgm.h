/** This header file contains input validation functions that are used
for image processing executables*/

/** Maximum intensity value expected for images. */
#define STD_RANGE 255

/** Exit code for a bad magic number or other bad input in the header. */
#define BAD_HEADER 255

/** Exit code for bad or missing pixel data */
#define BAD_PIXEL 254

/**Reads the first line of the input to ensure it is the proper file type*/
void checkType();

/**Reads the dimensions of the image*/
int readDimension();

/**Reads the maximum range for a pixel*/
void checkRange();

/**Checks for comments and returns the first character for a line that isn't a comment*/
char checkComment();

/**Skips a line if the comment flag '#' is detected*/
void skipLine();

/**Converts a line of input that starts with a character that is a digit 1-9 to an integer*/
int convertCharToInt(char c);

/**Checks a line for leading whitespace*/
char checkLeadingWhitespace();

/**Reads the pixels of the array*/
void readPixels( int height, int width, unsigned char pix[ height ][ width ] );

/**Writes the output image from the processing to a unsigned char array*/
void writeImage( int height, int width, unsigned char pix[ height ][ width ] );