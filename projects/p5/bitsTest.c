#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bits.h"

#define TESTFILE "testfile.bin"

int main()
{
  // A test for writing exactly 8 bits with bitWriter.
  {
    // Make a bit writer sending bits to a test file
    BitWriter *writer = openBitWriter( TESTFILE );

    // Write out a sequence of 8 bits.
    putBit( writer, 0 );
    putBit( writer, 1 );
    putBit( writer, 1 );
    putBit( writer, 1 );
    putBit( writer, 0 );
    putBit( writer, 0 );
    putBit( writer, 1 );
    putBit( writer, 1 );

    // Finish writing.
    closeBitWriter( writer );

    // Make sure we wrote out what we expected.
    FILE *fp = fopen( TESTFILE, "r" );

    // Make sure testfile the exists.
    assert( fp );

    // Make sure the file is the right size, should be 1 byte.
    unsigned char buffer[ 10 ];
    assert( fread( buffer, sizeof( buffer[ 0 ] ), sizeof( buffer ), fp ) == 1 );

    // Make sure that byte contains the values it should.
    assert( buffer[ 0 ] = 0x73 );

    fclose( fp );
  }

  // A test for writing exactly 16 bits with bitWriter.
  {
    // Make a bit writer sending bits to the test file
    BitWriter *writer = openBitWriter( TESTFILE );

    // Write out a sequence of 16 bits.
    putBit( writer, 1 );
    putBit( writer, 1 );
    putBit( writer, 0 );
    putBit( writer, 0 );
    putBit( writer, 1 );
    putBit( writer, 0 );
    putBit( writer, 1 );
    putBit( writer, 0 );

    putBit( writer, 1 );
    putBit( writer, 0 );
    putBit( writer, 0 );
    putBit( writer, 1 );
    putBit( writer, 0 );
    putBit( writer, 1 );
    putBit( writer, 1 );
    putBit( writer, 0 );

    // Finish writing.
    closeBitWriter( writer );

    // Make sure we wrote out what we expected.
    FILE *fp = fopen( TESTFILE, "r" );

    // Make sure testfile the exists.
    assert( fp );

    // Make sure the file is the right size, should be 2 bytes this time.
    unsigned char buffer[ 10 ];
    assert( fread( buffer, sizeof( buffer[ 0 ] ), sizeof( buffer ), fp ) == 2 );

    // Make sure the two bytes contain the values they should.
    assert( buffer[ 0 ] = 0xCA );
    assert( buffer[ 2 ] = 0x96 );

    fclose( fp );
  }

  // A test for writing exactly 10 bits.  Remaining bits in the second byte should get a value
  // of zero.
  {
    // Make a bit writer sending bits to the testfile
    BitWriter *writer = openBitWriter( TESTFILE );

    // Write out a sequence of 10 bits.
    putBit( writer, 1 );
    putBit( writer, 0 );
    putBit( writer, 1 );
    putBit( writer, 1 );
    putBit( writer, 0 );
    putBit( writer, 0 );
    putBit( writer, 1 );
    putBit( writer, 0 );

    putBit( writer, 1 );
    putBit( writer, 1 );

    // Finish writing.
    closeBitWriter( writer );

    // Make sure we wrote out what we expected.
    FILE *fp = fopen( TESTFILE, "r" );

    // Make sure testfile the exists.
    assert( fp );

    // Make sure the file is the right size, 10 bits should require 2 bytes.
    unsigned char buffer[ 10 ];
    assert( fread( buffer, sizeof( buffer[ 0 ] ), sizeof( buffer ), fp ) == 2 );

    // Make sure the two bytes contain the values they should.
    assert( buffer[ 0 ] = 0xB2 );
    assert( buffer[ 2 ] = 0xC0 );

    fclose( fp );
  }
  
  // Test for BitReader, reading one byte.
  {
    // Prepare a file with a particular sequence of 8 bits.
    FILE *fp = fopen( TESTFILE, "w" );
    if ( ! fp ) {
      fprintf( stderr, "Can't create test file: %s\n", TESTFILE );
      exit( EXIT_FAILURE );
    }
    // Make sure the file is the right size, 10 bits should require 2 bytes.
    unsigned char buffer[] = { 0xA7 };
    if ( fwrite( buffer, sizeof( buffer[ 0 ] ), sizeof( buffer ), fp ) != 1 ) {
      fprintf( stderr, "Can't write data to the test file: %s\n", TESTFILE );
      exit( EXIT_FAILURE );
    }

    fclose( fp );
    
    // Make a bit reader getting bits from "testfile.bin"
    BitReader *reader = openBitReader( "testfile.bin" );

    // Make sure we get the right sequence of bits from this file.
    assert( getBit( reader ) == 1 );
    assert( getBit( reader ) == 0 );
    assert( getBit( reader ) == 1 );
    assert( getBit( reader ) == 0 );
    assert( getBit( reader ) == 0 );
    assert( getBit( reader ) == 1 );
    assert( getBit( reader ) == 1 );
    assert( getBit( reader ) == 1 );

    // Make sure we get an EOF when we run out of bits.
    assert( getBit( reader ) == EOF );

    // Finish writing.
    closeBitReader( reader );
  }

  // Test for BitReader, reading from a two-byte file.
  {
    // Prepare a file with a particular sequence of 8 bits.
    FILE *fp = fopen( TESTFILE, "w" );
    if ( ! fp ) {
      fprintf( stderr, "Can't create test file: %s\n", TESTFILE );
      exit( EXIT_FAILURE );
    }
    // Make sure the file is the right size, 10 bits should require 2 bytes.
    unsigned char buffer[] = { 0x07, 0xF3 };
    if ( fwrite( buffer, sizeof( buffer[ 0 ] ), sizeof( buffer ), fp ) != 2 ) {
      fprintf( stderr, "Can't write data to the test file: %s\n", TESTFILE );
      exit( EXIT_FAILURE );
    }

    fclose( fp );
    
    // Make a bit reader getting bits from "testfile.bin"
    BitReader *reader = openBitReader( "testfile.bin" );

    // Make sure we get the right sequence of bits from this file.
    assert( getBit( reader ) == 0 );
    assert( getBit( reader ) == 0 );
    assert( getBit( reader ) == 0 );
    assert( getBit( reader ) == 0 );
    assert( getBit( reader ) == 0 );
    assert( getBit( reader ) == 1 );
    assert( getBit( reader ) == 1 );
    assert( getBit( reader ) == 1 );

    assert( getBit( reader ) == 1 );
    assert( getBit( reader ) == 1 );
    assert( getBit( reader ) == 1 );
    assert( getBit( reader ) == 1 );
    assert( getBit( reader ) == 0 );
    assert( getBit( reader ) == 0 );
    assert( getBit( reader ) == 1 );
    assert( getBit( reader ) == 1 );

    // Make sure we get an EOF when we run out of bits.
    assert( getBit( reader ) == EOF );

    // Finish writing.
    closeBitReader( reader );
  }

  // If we get to here, tests must have run successfully.
  printf( "Tests ran successfully\n" );

  return EXIT_SUCCESS;
}
