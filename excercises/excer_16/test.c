#include <stdio.h>
#include <stdbool.h>
#include <assert.h>


unsigned short increment4to7( unsigned short s )
{
  unsigned short bitField = ( s & 0x00F0 ) >> 4;
  bitField++;
  s &= 0x00FF;
  s |=  ( ( bitField << 4 ) & 0x00F0 );
  return s;
}

int main() {
unsigned short a = 0x0f00;
unsigned short b = 0x00F0;
unsigned short c = a | b;
printf("%04x\n", c);
}

