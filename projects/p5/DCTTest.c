#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "j10.h"

// How close we expect to get to the right result after transformation.
#define EPSILON 0.0000000000001

int main( int argc, char *argv[] )
{
  // A random block of values to run throught he DCT.
  double X[ BLOCK_SIZE ][ BLOCK_SIZE ] = {
    { 6.80, -2.11,  5.66,  5.97,  8.23, -6.05, -3.30,  5.36, -4.44,  1.08 },
    { -0.45,  2.58, -2.70,  0.27,  9.04,  8.32,  2.71,  4.35, -7.17,  2.14 },
    { -9.67, -5.14, -7.26,  6.08, -6.87, -1.98, -7.40, -7.82,  9.98, -5.63 },
    { 0.26,  6.78,  2.25, -4.08,  2.75,  0.49, -0.13,  9.46, -4.15,  5.43 },
    { 0.53,  5.40, -2.00,  7.83, -4.33, -2.95,  6.15,  8.38, -8.60,  8.99 },
    { 0.52, -8.28, -6.16,  3.26,  7.80, -3.02, -8.72, -9.60, -0.85, -8.74 },
    { -5.23,  9.41,  8.04,  7.02, -4.67,  0.80, -2.50,  5.20,  0.25,  3.35 },
    { 0.63, -9.21, -1.25,  8.64,  8.62,  4.42, -4.31,  4.77,  2.80, -2.92 },
    { 3.76, -6.68, -1.20,  7.60,  6.58, -3.39, -5.42,  7.87, -2.99,  3.73 },
    { 9.13,  1.77,  3.15,  7.17, -1.21,  8.48, -2.03,  6.30,  3.68,  8.22 }
  };

  // Apply the DCT.
  double Y[ BLOCK_SIZE ][ BLOCK_SIZE ];
  DCTBlock( X, Y );

  // Expected results from the transformation, according to our definition of the DCT.
  double expectedY[ BLOCK_SIZE ][ BLOCK_SIZE ] = {
    { 0.42130691100000,  0.05092680500632, -0.21152914098823, -0.41604066334643,  0.04866271207186,  0.52147023300000,  0.21870624360318, -0.26933943772849,  0.27256375320504, -0.48025418762426 },
    { -0.29038417067842,  0.05703979851448, -0.06739195319562,  0.11592131307829, -0.03231937546038, -0.22833092765040, -0.10090128961175, -0.27285387287156, -0.12634087934841,  0.20317172655318 },
    { 0.41740950673637,  0.01125467926594, -0.01958104895185,  0.01518103301272,  0.20219555933212,  0.25652201680933,  0.07188815303785,  0.13767914865244,  0.32583333131489,  0.02678622897361 },
    { -0.06823380146483,  0.28796767675965, -0.31458986039129, -0.22281491873102, -0.04356213235334,  0.26644715360743, -0.01324917677239,  0.00921215801074,  0.12225413724726,  0.22173299893244 },
    { 0.25703427518040,  0.31683606680104,  0.24935224641183,  0.11117317202656,  0.12895666721264, -0.08102373123089,  0.35752012270995, -0.23344994962354,  0.17783818068780,  0.06994490876270 },
    { 0.27803646300000, -0.01677348725159,  0.06470399944954,  0.09744148718814, -0.09287672835481,  0.18759249300000,  0.39561690534629, -0.45935107536109,  0.43914676301764,  0.10825207280083 },
    { 0.35649851013631,  0.06974157386492,  0.38405484053785, -0.04769209926719, -0.40511615398327, -0.30882831855570, -0.19887938604815,  0.09659135932146,  0.09338413188264, -0.09080243022547 },
    { -0.65706245991175,  0.10456467518851,  0.06194688190458, -0.32175767407689,  0.03202321094287,  0.51890706573683, -0.14741337572333,  0.27336139440369, -0.12089002874479,  0.29538906181115 },
    { -0.41505066042514, -0.09325151642946, -0.12767547053493, -0.19335388547948,  0.10071574781220,  0.47040854727972,  0.01284633507451,  0.57485748387488, -0.39434897321264,  0.05290090527484 },
    { 0.07957114212533, -0.10664951561933,  0.34033491426374, -0.18358294482007, -0.49775666333812, -0.27795706147900,  0.28535482326920, -0.05417121117778, -0.27047092922469, -0.31407750718715 }
  };

  // Check each result and make sure it's really close to the expected value.
  for ( int r = 0; r < BLOCK_SIZE; r++ ) {
    for ( int c = 0; c < BLOCK_SIZE; c++ ) {
      if ( fabs( Y[ r ][ c ] - expectedY[ r ][ c ] ) > EPSILON ) {
        printf( "bad result from DCT\n" );
        printf( "Y[ %d ][ %d ] = %17.14f\n", r, c, Y[ r ][ c ] );
        printf( "expectedY[ %d ][ %d ] = %17.14f\n", r, c, expectedY[ r ][ c ] );
        exit( EXIT_FAILURE );
      }
    }
  }

  // Apply the DCT again, it should give us back the original block.
  double Z[ BLOCK_SIZE ][ BLOCK_SIZE ];
  IDCTBlock( Y, Z );

  // Check the results and make sure results are close to the expected values.
  for ( int r = 0; r < BLOCK_SIZE; r++ ) {
    for ( int c = 0; c < BLOCK_SIZE; c++ ) {
      if ( fabs( Z[ r ][ c ] - X[ r ][ c ] ) > EPSILON ) {
        printf( "bad result from inverse DCT\n" );
        printf( "Z[ %d ][ %d ] = %17.14f\n", r, c, Z[ r ][ c ] );
        printf( "X[ %d ][ %d ] = %17.14f\n", r, c, X[ r ][ c ] );
        exit( EXIT_FAILURE );
      }
    }
  }
  
  return EXIT_SUCCESS;
}
