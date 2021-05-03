#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

// One inch equals this many meters.
#define INCHES_TO_METERS 0.0254

// Representation for for an imperial measurement, as a length in
// inches.  The length is represented as a mixed numeral, with an
// integer number of inches and a simple fraction represented as
// numerator and denominator.  So, in inches, the length would be
// equivalent to inches + numerator / denominator.
typedef struct {
  int inches;
  int numerator;
  int denominator;
} ImperialLength;

// Remptesentation for a type of item in our inventory, with
// a length that's measured in metric or imperial units.
typedef struct {
  // Unique ID for this type of item.
  int sku;

  // Enumeration to indicate whether this is a metric or an imperial
  // measurement.
  enum { metric, imperial } mtype;

  // Length, represented in either imperial units (as an instance of
  // ImperialLength) or metric (as a double).  The mtype field says
  // which element of this union we're using.
  union {
    double mval;
    ImperialLength ival;
  } length;
} Item;

// Print a usage message, and exit unsuccessfully.
static void usage()
{
  fprintf( stderr, "usage: inventory <inventory-file>\n" );
  exit( EXIT_FAILURE );
}

// Complain if the inventory file is bad.
static void invalid()
{
  fprintf( stderr, "Invalid inventory file\n" );
  exit( EXIT_FAILURE );
}

// Comparison function for sorting items.
int itemComp( void const *pA, void const *pB )
{
  // These two pointers are really pointers to items.
  Item const *itemA = (Item *) pA;
  Item const *itemB = (Item *) pB;
 
 double metricLengthA = 0;
 double metricLengthB = 0;
 double fractionA = 0;
 double fractionB = 0;
  // Compare the length of the items pointed to by itemA and itemB.
  //...
  if ( itemA->mtype == imperial ) {
  	metricLengthA = itemA->length.ival.inches * INCHES_TO_METERS;
  	double fractionA = (double)(itemA->length.ival.numerator) / (double)(itemA->length.ival.denominator);
  	fractionA *= INCHES_TO_METERS;
  	metricLengthA += fractionA;
  	//printf("%lf\n", metricLengthA);
  }

  if ( itemB->mtype == imperial ) {
  	metricLengthB = itemB->length.ival.inches * INCHES_TO_METERS;
  	double fractionB = (double)(itemB->length.ival.numerator) / (double)(itemB->length.ival.denominator);
  	fractionB *= INCHES_TO_METERS;
  	metricLengthB += fractionB;
  	  	//printf("%lf\n", metricLengthB);
  }

  if (itemA->mtype == imperial && itemB->mtype == imperial ) {
  	if (metricLengthA > metricLengthB ) {
  		return 1;
  	}
  	if (metricLengthB > metricLengthA ) {
  		return -1;
  	}
  	return 0;
  }

  if (itemA-> mtype == imperial && itemB->mtype == metric) {
  	if (metricLengthA > itemB->length.mval) {
  		return 1;
  	}
  	if (itemB->length.mval > metricLengthA) {
  		return -1;
  	}
  	return 0;
  }

  if (itemA->mtype == metric && itemB->mtype == imperial) {
  	if (itemA->length.mval > metricLengthB ) {
  		return 1;
  	}
  	if (metricLengthB > itemA->length.mval) {
  		return -1;
  	}
  	return 0;
  }

  if (itemA->mtype == metric && itemB->mtype == metric) {
  	if (itemA->length.mval > itemB->length.mval) {
  		return 1;
  	}
  	if (itemB->length.mval > itemA->length.mval) {
  		return -1;
  	}
  	return 0;
  }

  return 0;
}

int main( int argc, char *argv[] )
{
  // Validate input arguments, and open the inventory input file.
  if ( argc != 2 )
    usage();

  FILE *fp = fopen( argv[ 1 ], "r" );
  if ( !fp ) {
    fprintf( stderr, "Can't open input file: %s\n", argv[ 1 ] );
    exit( EXIT_FAILURE );
  }

  // Read the inventory, first the number of items.
  int icount;
  if ( fscanf( fp, "%d", &icount ) != 1 )
    invalid();

  // Then, read all the inventory items.
  Item *ilist = (Item *) malloc( icount * sizeof( Item ) );
  for ( int i = 0; i < icount; i++ ) {
    // Read an item and store it in element i of ilist.
    // ...
    int id;
    char units;
    int whole;
    int num;
    int den;
    double metricfloat;
    fscanf( fp, "%d%*c%c%*c", &id, &units );
    if (units == 'i') {
    	fscanf(fp, "%d%*c%d%*c%*c%*c%d", &whole, &num, &den);
    	ilist[i].sku = id;
    	ilist[i].mtype = imperial;
    	ilist[i].length.ival.inches = whole;
    	ilist[i].length.ival.numerator = num;
    	ilist[i].length.ival.denominator = den;

    }
    else {
    	fscanf( fp, "%lf", &metricfloat );
    	ilist[i].sku = id;
    	ilist[i].mtype = metric;
    	ilist[i].length.mval = metricfloat;
    }


  }

  // Sort the items by length.
  qsort( ilist, icount, sizeof( Item ), itemComp );

  // Print out the sorted list, in the same format as the input.
  printf( "%d\n", icount );
  for ( int i = 0; i < icount; i++ ) {
    // Print item i from ilist, with a real-valued length if it's metric, or
    // as a mixed numeral if it's metric.
    // ...
    if (ilist[i].mtype == metric) {
    	printf("%d m %lf\n", ilist[i].sku, ilist[i].length.mval);
    }
    else {
    	printf("%d i %d %d / %d\n", ilist[i].sku, ilist[i].length.ival.inches, ilist[i].length.ival.numerator, ilist[i].length.ival.denominator);
    }
  }

  // Free the resources and exit successfully.
  free( ilist );
  fclose( fp );
  return EXIT_SUCCESS;
}
