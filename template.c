/**
    I copied and pasted the text for the header in main direclty from
    the project description.  However, the output in the body of the program
    use 10 character fields even though the header uses 11.
*/
#include<stdio.h>
int main() {
struct ABCD {
  int a;
  int b;
  int c;
  int d;
};
 
  struct ABCD x = { 5, 10, 15, 20 };
  printf( "%d\n", x.c );
  return 1;
}