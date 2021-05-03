#!/bin/bash
FAIL=0

# Function to run a test and check its output and exit status against
# expected.
checkResults() {
  TESTNO=$1
  ESTATUS=$2
  STATUS=$3

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** Test $TESTNO FAILED - incorrect exit status. Expected: $ESTATUS Got: $STATUS"
      FAIL=1
      return 1
  fi

  # Make sure the output matches the expected output.
  if ! diff -q expected-$TESTNO.pgm output.pgm >/dev/null 2>&1 ; then
      echo "**** Test $TESTNO FAILED - output didn't match the expected output"
      FAIL=1
      return 1
  fi

  echo "Test $TESTNO PASS"
  return 0
}

# Build and test each of the programs.
make clean

# Give an error message if the clean rule doesn't seem to delete the
# files it's supposed to.
if [ -f rotate ] || [ -f frame ] || [ -f mirror ] ||
   [ -f pgm.o ] || [ -f rotate.o ] || [ -f frame.o ] || [ -f mirror.o ]; then
    echo "**** The makefile clean rule doesn't seem to be working"
    fail=1
fi

# Run tests for just the rotate program
make rotate

if [ -x rotate ] ; then
    echo "Test 01 : ./rotate < image-a.pgm > output.pgm"
    ./rotate < image-a.pgm > output.pgm
    checkResults 01 0 $?

    echo "Test 02 : ./rotate < image-b.pgm > output.pgm"
    ./rotate < image-b.pgm > output.pgm
    checkResults 02 0 $?

    echo "Test 03 : ./rotate < image-d.pgm > output.pgm"
    ./rotate < image-d.pgm > output.pgm
    checkResults 03 0 $?

    echo "Test 04 : ./rotate < image-e.pgm | ./rotate | ./rotate > output.pgm"
    ./rotate < image-e.pgm | ./rotate | ./rotate > output.pgm
    checkResults 04 0 $?

    echo "Test 05 : ./rotate < image-f.pgm > output.pgm"
    ./rotate < image-f.pgm > output.pgm
    checkResults 05 255 $?

else
    echo "**** The rotate program didn't compile successfully"
    FAIL=1
fi

make frame

# Run tests for just the frame program
if [ -x frame ] ; then
    echo "Test 06 : ./frame < image-c.pgm > output.pgm"
    ./frame < image-c.pgm > output.pgm
    checkResults 06 0 $?

    echo "Test 07 : ./frame < image-d.pgm > output.pgm"
    ./frame < image-d.pgm > output.pgm
    checkResults 07 0 $?

    echo "Test 08 : ./frame < image-e.pgm > output.pgm"
    ./frame < image-e.pgm > output.pgm
    checkResults 08 0 $?

    echo "Test 09 : ./frame < image-g.pgm > output.pgm"
    ./frame < image-g.pgm > output.pgm
    checkResults 09 255 $?

else
    echo "**** The frame program didn't compile successfully"
    FAIL=1
fi

make mirror

# Run tests for just the mirror program
if [ -x mirror ] ; then
    echo "Test 10 : ./mirror < image-d.pgm > output.pgm"
    ./mirror < image-d.pgm > output.pgm
    checkResults 10 0 $?

    echo "Test 11 : ./mirror < image-e.pgm > output.pgm"
    ./mirror < image-e.pgm > output.pgm
    checkResults 11 0 $?

    echo "Test 12 : ./mirror < image-c.pgm > output.pgm"
    ./mirror < image-c.pgm > output.pgm
    checkResults 12 0 $?

    echo "Test 13 : ./mirror < image-h.pgm > output.pgm"
    ./mirror < image-h.pgm > output.pgm
    checkResults 13 254 $?

    echo "Test 14 : ./mirror < image-i.pgm > output.pgm"
    ./mirror < image-i.pgm > output.pgm
    checkResults 14 254 $?

else
    echo "**** The mirror program didn't compile successfully"
    FAIL=1
fi

# Run tests with all three transformations
if [ -x rotate ] && [ -x frame ] && [ -x  ] ; then
    echo "Test 15 : ./rotate < image-d.pgm | ./frame | ./mirror > output.pgm"
    ./rotate < image-d.pgm | ./frame | ./mirror > output.pgm
    checkResults 15 0 $?

    echo "Test 16 : ./mirror < image-d.pgm | ./frame | ./rotate > output.pgm"
    ./mirror < image-d.pgm | ./frame | ./rotate > output.pgm
    checkResults 16 0 $?

else
    echo "**** At least one of your programs didn't compile successfully."
    FAIL=1
fi

if [ $FAIL -ne 0 ]; then
  echo "**** There were failing tests"
  exit 1
else 
  echo "Tests successful"
  exit 0
fi
