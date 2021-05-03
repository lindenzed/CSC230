#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main()
{
  // Open the input file and print an error message if we're unsuccessful.
  // (the error message is mostly to help you with debugging.  We won't test
  // this behavior).
  // ...
  FILE *fp = fopen( "input.txt", "r" );
  char firstName[11];
  char lastName[11];
  char id[8];
  char ph1[3];
  char ph2[3];
  char ph3[4];
  char ch;
  char ch2;
  //int match = fscanf(fp, "%11s%11s %*[0-9] %8[^@]%*s%*s %[0-9] %*[-] %[0-9] %*[-] %[0-9]%*[^\n]", firstName, lastName, id, ph1, ph2, ph3 );
  //printf("First: %s\nLast: %s\nID: %s\nPhone:%s %s %s\nMatch: %d\n", firstName, lastName, id, ph1, ph2, ph3, match );


  // Counting input lines, so we can report errors.
  int lineCount = 1;
  while (ch != EOF) {
 if ( fscanf(fp, "%11s%11s %*[0-9] %8[^@]%*[@]%*s%*s %[0-9] %*[-] %[0-9] %*[-] %[0-9]%*[^\n]", firstName, lastName, id, ph1, ph2, ph3 ) == 6 ) {
  fprintf(stdout, "%8s %11s %11s (%s)%s-%s\n", id, firstName, lastName, ph1, ph2, ph3);
  lineCount++;
  continue;
 }
 else {
    fscanf(fp, "%*[^\n]");
 }
 ch = getc(fp);
 ch2 = getc(fp);
 if (ch2 == EOF) {
  lineCount++;
  continue;
 }
 fprintf(stderr, "Invalid input, line %d\n", lineCount );
 ungetc(ch2, fp);
 lineCount++;
}
  // Keep reading input lines until we reach the end-of-file.
  // Write an output line or an error message for each one.
  // ...

  return EXIT_SUCCESS;
}
