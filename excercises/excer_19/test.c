#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

int main()
{


while ( ! feof( stdin ) ) {
   int ch = getchar();
   printf( "%d\n", ch );
}
}
