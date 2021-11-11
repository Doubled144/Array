/*
  Filename   : ArrayDriver.cc
  Author     : Gary M. Zoppetti
  Course     : CSCI 362-01
  Assignment : N/A
  Description: Test some, but NOT ALL, methods of the Array class.
*/   

/************************************************************/
// System includes

#include <cstdlib>
#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <cassert>

/************************************************************/
// Local includes

#include "Array.hpp"

/************************************************************/
// Using declarations

using std::cin;
using std::cout;
using std::endl;
using std::ostream_iterator;
using std::string;
using std::ostringstream;

/************************************************************/
// Function prototypes/global vars/typedefs

void
printTestResult (const string& test,
		 const string& expected,
		 const ostringstream& actual);

/************************************************************/

int      
main (int argc, char* argv[]) 
{        
  Array<int> A;

  // For holding the actual result
  ostringstream output;
  // Put the actual result into the output stream
  output << A;
  printTestResult ("no-arg ctor", "[ ]", output);

  // Must clear the output stream each time
  output.str ("");
  output << A.empty ();
  // "1" for true, "0" for false
  printTestResult ("empty", "1", output);
  
  A.push_back (5);
  A.push_back (10);
  A.push_back (15);

  output.str ("");
  output << A;
  printTestResult ("push_back", "[ 5 10 15 ]", output);

  output.str ("");
  output << A.size ();
  printTestResult ("size", "3", output);
  
  A.pop_back ();
  A.pop_back ();

  output.str ("");
  output << A;
  printTestResult ("pop_back", "[ 5 ]", output);

  /************************************************************/
  // Convert the following tests to use printTestResult
  /************************************************************/

  for (int i = 0; i < 10; ++i)
  {
    A.insert (A.begin (), i);
  }   
  output.str ("");
  output << A;
  printTestResult ("insert", "[ 9 8 7 6 5 4 3 2 1 0 5 ]", output);

  for (Array<int>::iterator i = A.begin (); i != A.end (); )
  {
    i = A.erase (i);
  }
  output.str ("");
  output << A;
  printTestResult ("erase", "[ ]", output);

  // Size ctor, with a fill value. 
  Array<int> B (3, 9);
  output.str ("");
  output << B;
  printTestResult ("size ctor", "[ 9 9 9 ]", output);

  // Range ctor. 
  Array<int> C (B.begin (), B.begin () + 2);
  output.str ("");
  output << C;
  printTestResult ("range ctor", "[ 9 9 ]", output);

  // Assignment operator. 
  B = A;
  output.str ("");
  output << B;
  printTestResult ("assignment op.", "[ ]", output);
  
  for (int i = 0; i < 5; ++i)
  {
    B.insert (B.begin (), i);
  }
  output.str ("");
  output << B;
  printTestResult ("insert with range", "[ 4 3 2 1 0 ]", output);

  /************************************************************/
  // START WRITING YOUR TESTS HERE
  /************************************************************/

  // Test range ctor (a different case than I test above)
  Array<int> D (B.begin () + (B.size ()/2), B.end ());
  output.str ("");
  output << D;
  printTestResult ("range ctor", "[ 2 1 0 ]", output);

  // Test copy ctor
  Array<int> E (D);
  output.str ("");
  output << E;
  printTestResult ("copy ctor", "[ 2 1 0 ]", output);

  // Test capacity
  E.insert (E.begin (), 3);
  E.insert (E.begin (), 4);
  output.str ("");
  output << E.capacity ();
  printTestResult ("capacity", "7", output);

  // Test subscript operator
  E[0] = 9;
  E[4] = (-10);
  output.str ("");
  output << E;
  printTestResult ("subscript operator", "[ 9 3 2 1 -10 ]", output);

  // Test reserve
  E.reserve (5);
  output.str ("");
  output << E.capacity ();
  printTestResult ("reserve", "7", output);

  // Test reserve (2nd case)
  E.reserve (10);
  output.str ("");
  output << E.capacity ();
  printTestResult ("reserve (2nd case)", "10", output);

  // Test resize
  E.resize (10);
  output.str ("");
  output << E;
  printTestResult ("resize", "[ 9 3 2 1 -10 0 0 0 0 0 ]", output);

  // Test resize (2nd case)
  E.resize (4);
  output.str ("");
  output << E;
  printTestResult ("resize (2nd case)", "[ 9 3 2 1 ]", output);

  // Test iterator (begin)
  int i = *E.begin ();
  output.str ("");
  output << i;
  printTestResult ("iterator", "9", output);

  return EXIT_SUCCESS;
}

/************************************************************/

void
printTestResult (const string& test,
		 const string& expected,
		 const ostringstream& actual)
{
  cout << "Test: " << test << endl;
  cout << "==========================" << endl;
  cout << "Expected: " << expected << endl;
  cout << "Actual  : " << actual.str () << endl;
  cout << "==========================" << endl << endl;

  // Ensure the two results are the same
  assert (expected == actual.str ());
}

/************************************************************/
