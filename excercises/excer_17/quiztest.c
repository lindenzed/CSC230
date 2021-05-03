#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define A
#ifdef A
#define B
#endif

#ifndef B
printf( "Hello World\n" );
#elif defined( A )
printf( "Bonjour le monde\n" );
#else
printf( "Hallo Welt\n" );
#endif



