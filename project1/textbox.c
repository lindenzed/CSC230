/**
    @file textbox.c
    @author Zach Giles (zgiles)
    This program consumes input and prints the input in a text box.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** Width of each line of text in the box. */
#define LINE_WIDTH 60

/** Symbol used to draw the border around the box. */
#define BORDER '*'

/**
    The paddedLine function consumes and prints the input
    formatted to be in the text box rectangle/square.
    @return true if input is consumed and printed, false if at EOF
  */
bool paddedLine()
{
    int c = getchar();
    int charCount = 0;
    //If at end of file return false.
    if (c == EOF){
        return false;
    }
    /*Consume input and print to file until EOF, end of line, or 60 
    characters are reached.  Condition is LINE_WIDTH - 1 becuase first character is
    printed in the main() to check if EOF or empty line*/
    while ( c != EOF  && c != '\n' && charCount < LINE_WIDTH - 1) {
        printf("%-c", c);
        c = getchar();
        charCount++;
    }
    /*If over 60 characters continue to end of line w/o printing*/
    if (charCount == LINE_WIDTH - 1) {
        while (c != EOF && c != '\n') {
            c = getchar();
        }
    }
    /*If under 60 characters add spaces until 60 characters
    condition is LINE_WIDTH - 1 becuase first character is
    printed in the main() to check if EOF or empty line*/
    while (charCount < LINE_WIDTH - 1) {
        printf("%-c", ' ');
        charCount++;
    }
    return true;
}

/**
    The lineOfChars prints the top and bottom border
    @param ch character that you want the border to be
    @param count the width of the lines in the text box
  */
void lineOfChars( char ch, int count )
{
    printf("%c", ch);
    while(count > 0) {
        printf("%c", ch);
        count--;
    }
    printf("%c\n", ch);
}



/**
    The main program first prints the top border then consumes and prints
    the formatted input. Once the EOF is reach the bottom border is printed
  */
int main()
{
    int check = getchar();
    if (check == EOF) {
        return 0;
    }
    lineOfChars(BORDER, LINE_WIDTH);//top border
    while (check != EOF) {
        printf("%c", BORDER);
        //if first character is new line (i.e. blank line)
        if (check == '\n') {
            int emptyCounter = 0;
            while (emptyCounter < LINE_WIDTH) {
                printf("%-c", ' ');
                emptyCounter++;
            }
            printf("%-c\n", BORDER);
        }
        //what to do if first character isn't a new line
        if (check != '\n') {
            printf("%c", check);//print the first character
            paddedLine();//consumes input and prints it out
            printf("%-c\n", BORDER);//prints the ending astrisk with a new line
        } 
        check = getchar();  //checks first character of next line
    }
    lineOfChars(BORDER, LINE_WIDTH);//prints bottom border
    return 0;
}
