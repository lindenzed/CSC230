#!/bin/bash
FAIL=0

# Function to check the output of the encrypt program after it's run, including checking
# an output file, standard output, standard error and exit status.
checkEncryptResults() {
  TESTNO=$1
  ESTATUS=$2
  STATUS=$3

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** Test $TESTNO FAILED - Expected an exit status of $ESTATUS, bug got: $STATUS"
      FAIL=1
      return 1
  fi

  # if there's an expected output file, make sure the program also has one
  # that matches.  If there's no expected output file, then the program
  # shouldn't write an output file.
  if [ -f encrypted-$TESTNO.txt ]; then
      # Make sure the output file contains correct output.
      if ! diff -q encrypted-$TESTNO.txt output.txt >/dev/null 2>&1 ; then
	  echo "**** Test $TESTNO FAILED - output file didn't match expected."
	  FAIL=1
	  return 1
      fi
  else
      if [ -f output.txt ]; then
	  echo "**** Test $TESTNO FAILED - the program wrote an output file but it shouldn't for this test case."
	  FAIL=1
	  return 1
      fi
  fi

  # Make sure the output to stdout matches expected.
  if ! diff -q estdout-$TESTNO.txt stdout.txt >/dev/null 2>&1 ; then
      echo "**** Test $TESTNO FAILED - output to stdout didn't match expected"
      FAIL=1
      return 1
  fi

  # Make sure the output to stderr matches expected.
  if ! diff -q estderr-$TESTNO.txt stderr.txt >/dev/null 2>&1 ; then
      echo "**** Test $TESTNO FAILED - output to stderr didn't match expected"
      FAIL=1
      return 1
  fi

  echo "Test $TESTNO PASS"
  return 0
}

# Function to check the output of the decrypt program after it's run, including checking
# an output file, standard output, standard error and exit status.
checkDecryptResults() {
  TESTNO=$1
  ESTATUS=$2
  STATUS=$3
  ORIGINAL=$4

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** Test $TESTNO FAILED - Expected an exit status of $ESTATUS, bug got: $STATUS"
      FAIL=1
      return 1
  fi

  # if there's an expected output file, make sure the program also has one
  # that matches.  If there's no expected output file, then the program
  # shouldn't write an output file.
  if [ -f encrypted-$TESTNO.txt ]; then
      # Make sure the output file contains correct output.
      if ! diff -q $ORIGINAL output.txt >/dev/null 2>&1 ; then
	  echo "**** Test $TESTNO FAILED - output file didn't match original file."
	  FAIL=1
	  return 1
      fi
  else
      if [ -f output.txt ]; then
	  echo "**** Test $TESTNO FAILED - the program wrote an output file but it shouldn't for this test case."
	  FAIL=1
	  return 1
      fi
  fi

  # Make sure the output to stdout matches expected.
  if ! diff -q estdout-$TESTNO.txt stdout.txt >/dev/null 2>&1 ; then
      echo "**** Test $TESTNO FAILED - output to stdout didn't match expected"
      FAIL=1
      return 1
  fi

  # Make sure the output to stderr matches expected.
  if ! diff -q estderr-$TESTNO.txt stderr.txt >/dev/null 2>&1 ; then
      echo "**** Test $TESTNO FAILED - output to stderr didn't match expected"
      FAIL=1
      return 1
  fi

  echo "Test $TESTNO PASS"
  return 0
}

# Try to get a fresh compile of the project.
make clean
make
if [ $? -ne 0 ]; then
    echo "**** Make didn't run succesfully when trying to build your program."
    FAIL=1
fi

# Run individual tests.  Since they each require different arguments, it didn't make
# as much sense to write a single test function for this.


# Test the encrypt program
echo
echo "Testing encrypt"
if [ -x encrypt ] ; then
    rm -f output.txt stdout.txt stderr.txt
    echo "Test 01: ./encrypt input-a.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt input-a.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 01 0 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 02: ./encrypt reverse input-a.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt reverse input-a.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 02 0 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 03: ./encrypt left input-a.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt left input-a.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 03 0 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 04: ./encrypt right input-a.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt right input-a.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 04 0 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 05: ./encrypt swap 2 4 input-a.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt swap 2 4 input-a.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 05 0 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 06: ./encrypt shift 1 input-a.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt shift 1 input-a.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 06 0 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 07: ./encrypt shift 10 input-a.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt shift 10 input-a.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 07 0 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 08: ./encrypt shift 25 input-a.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt shift 25 input-a.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 08 0 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 09: ./encrypt shift 3 reverse swap 2 4 left input-a.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt shift 3 reverse swap 2 4 left input-a.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 09 0 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 10: ./encrypt shift 12 reverse swap 15 8 shift 7 right swap 20 15 input-b.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt shift 12 reverse swap 15 8 shift 7 right swap 20 15 input-b.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 10 0 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 11: ./encrypt left swap 20 15 swap 1 26 shift 4 left input-b.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt left swap 20 15 swap 1 26 shift 4 left input-b.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 11 0 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 12: ./encrypt left right swap 12 14 swap 14 12 shift 13 shift 13 reverse reverse input-b.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt left right swap 12 14 swap 14 12 shift 13 shift 13 reverse reverse input-b.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 12 0 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 13: ./encrypt swap 2 3 reverse - output.txt < input-a.txt > stdout.txt 2> stderr.txt"
    ./encrypt swap 2 3 reverse - output.txt < input-a.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 13 0 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 14e: ./encrypt swap 2 3 reverse input-a.txt - > stdout.txt 2> stderr.txt"
    ./encrypt swap 2 3 reverse input-a.txt - > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 14e 0 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 15: ./encrypt reverse input-c.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt reverse input-c.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 15 1 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 16: ./encrypt reverse input-d.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt reverse input-d.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 16 1 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 17: ./encrypt reverse not-a-file.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt reverse not-a-file.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 17 1 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 18e: ./encrypt switch 2 3 reverse input-a.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt switch 2 3 reverse input-a.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 18e 1 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 19e: ./encrypt swap 2 6 input-a.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt swap 2 6 input-a.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 19e 1 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 20e: ./encrypt shift xyz input-a.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt shift xyz input-a.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 20e 1 $STATUS
    
    
   
else
    echo "**** Your encrypt program couldn't be tested since it didn't compile successfully."
    FAIL=1
fi

# Test the decrypt program
echo
echo "Testing decrypt"
if [ -x decrypt ] ; then
    rm -f output.txt stdout.txt stderr.txt
    echo "Test 01: ./decrypt encrypted-01.txt output.txt > stdout.txt 2> stderr.txt"
    ./decrypt input-a.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkDecryptResults 01 0 $STATUS input-a.txt

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 02: ./decrypt reverse encrypted-02.txt output.txt > stdout.txt 2> stderr.txt"
    ./encrypt reverse encrypted-02.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkDecryptResults 02 0 $STATUS input-a.txt

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 03: ./decrypt left encrypted-03.txt output.txt > stdout.txt 2> stderr.txt"
    ./decrypt left encrypted-03.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkDecryptResults 03 0 $STATUS input-a.txt

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 04: ./decrypt right encrypted-04.txt output.txt > stdout.txt 2> stderr.txt"
    ./decrypt right encrypted-04.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkDecryptResults 04 0 $STATUS input-a.txt

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 05: ./decrypt swap 2 4 encrypted-05.txt output.txt > stdout.txt 2> stderr.txt"
    ./decrypt swap 2 4 encrypted-05.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkDecryptResults 05 0 $STATUS input-a.txt

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 06: ./decrypt shift 1 encrypted-06.txt output.txt > stdout.txt 2> stderr.txt"
    ./decrypt shift 1 encrypted-06.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkDecryptResults 06 0 $STATUS input-a.txt

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 07: ./decrypt shift 10 encrypted-07.txt output.txt > stdout.txt 2> stderr.txt"
    ./decrypt shift 10 encrypted-07.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkDecryptResults 07 0 $STATUS input-a.txt

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 08: ./decrypt shift 25 encrypted-08.txt output.txt > stdout.txt 2> stderr.txt"
    ./decrypt shift 25 encrypted-08.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkDecryptResults 08 0 $STATUS input-a.txt 

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 09: ./decrypt shift 3 reverse swap 2 4 left encrypted-09.txt output.txt > stdout.txt 2> stderr.txt"
    ./decrypt shift 3 reverse swap 2 4 left encrypted-09.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkDecryptResults 09 0 $STATUS input-a.txt

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 10: ./decrypt shift 12 reverse swap 15 8 shift 7 right swap 20 15 encrypted-10.txt output.txt > stdout.txt 2> stderr.txt"
    ./decrypt shift 12 reverse swap 15 8 shift 7 right swap 20 15 encrypted-10.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkDecryptResults 10 0 $STATUS input-b.txt

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 11: ./decrypt left swap 20 15 swap 1 26 shift 4 left encrypted-11.txt output.txt > stdout.txt 2> stderr.txt"
    ./decrypt left swap 20 15 swap 1 26 shift 4 left encrypted-11.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkDecryptResults 11 0 $STATUS input-b.txt

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 12: ./decrypt left right swap 12 14 swap 14 12 shift 13 shift 13 reverse reverse encrypted-12.txt output.txt > stdout.txt 2> stderr.txt"
    ./decrypt left right swap 12 14 swap 14 12 shift 13 shift 13 reverse reverse encrypted-12.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkDecryptResults 12 0 $STATUS input-b.txt

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 13: ./decrypt swap 2 3 reverse - output.txt < encrypted-13.txt > stdout.txt 2> stderr.txt"
    ./decrypt swap 2 3 reverse - output.txt < encrypted-13.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkDecryptResults 13 0 $STATUS input-a.txt

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 14d: ./decrypt swap 2 3 reverse estdout-14e.txt - > stdout.txt 2> stderr.txt"
    ./decrypt swap 2 3 reverse estdout-14e.txt - > stdout.txt 2> stderr.txt
    STATUS=$?
    checkDecryptResults 14d 0 $STATUS input-a.txt

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 15: ./decrypt reverse input-c.txt output.txt > stdout.txt 2> stderr.txt"
    ./decrypt reverse input-c.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkDecryptResults 15 1 $STATUS input-c.txt

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 16: ./decrypt reverse input-d.txt output.txt > stdout.txt 2> stderr.txt"
    ./decrypt reverse input-d.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 16 1 $STATUS input-d.txt

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 17: ./decrypt reverse not-a-file.txt output.txt > stdout.txt 2> stderr.txt"
    ./decrypt reverse not-a-file.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 17 1 $STATUS not-a-file.txt

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 18d: ./decrypt switch 2 3 reverse input-a.txt output.txt > stdout.txt 2> stderr.txt"
    ./decrypt switch 2 3 reverse input-a.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkEncryptResults 18d 1 $STATUS

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 19d: ./decrypt swap 2 6 input-a.txt output.txt > stdout.txt 2> stderr.txt"
    ./decrypt swap 2 6 encrypted-05.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkDecryptResults 19d 1 $STATUS input-a.txt

    rm -f output.txt stdout.txt stderr.txt
    echo "Test 20d: ./decrypt shift xyz input-a.txt output.txt > stdout.txt 2> stderr.txt"
    ./decrypt shift xyz input-a.txt output.txt > stdout.txt 2> stderr.txt
    STATUS=$?
    checkDecryptResults 20d 1 $STATUS input-a.txt
   
else
    echo "**** Your decrypt program couldn't be tested since it didn't compile successfully."
    FAIL=1
fi


if [ $FAIL -ne 0 ]; then
  echo "**** There were failing tests"
  exit 1
else 
  echo "Tests successful"
  exit 0
fi
