#include <string>
#include <vector>
#include <fstream>
#include "Data.h"

using namespace std;
bool Data::open(char* filename)
{
	ifstream fin(filename, ifstream::in);

	while (fin.good()) {
		//fin.getline()
	}

	return false;
}
