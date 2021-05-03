// Pretend demonstration of conditional
// compilation with macros.

#include <stdio.h>

#if defined(LINUX)
   #define HDR "linux.h"
#elif defined(WIN32)
   #define HDR "windows.h"
#else
   #define HDR "default.h"
#endif

//#include HDR //not included b/c the files don't exist

int main(void)
{

   printf("%s\n", HDR);
   return 0;

}
