#include <iostream>
#include <fstream>

using namespace std;



int f( int a = 5, int b = 7, int c = 10 )
{
  return a + b + c;
}

int main()
{
cout << f( 4, 9);
}