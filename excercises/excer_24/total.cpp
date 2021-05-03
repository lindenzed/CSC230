#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	int value;
	int total = 0;
	ifstream input("numbers.txt");
  while (input >> value) {
  	total += value;
  }
  cout << "Total: " << total << endl;
}
