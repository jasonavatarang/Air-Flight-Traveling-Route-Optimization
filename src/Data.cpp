#include <string>
#include <vector>
#include <fstream>

#include <iostream>

#include "Data.h"

using namespace std;
bool Data::open(string filename)
{
	ifstream fin(filename, ifstream::in);
	if (!fin.good())
		return false;

	while (fin.good()) {
		Airport airport;
		string str;
		getline(fin, str);

		str = str.substr(str.find(',') + 1);
		str = str.substr(str.find(',') + 2);

		string name = str.substr(0, str.find('"'));
		for (int i = 0; i < name.size() && i < 30; i++)
			airport.name[i] = name[i];

		str = str.substr(str.find(',') + 1);
		str = str.substr(str.find(',') + 1);
		str = str.substr(str.find(',') + 1);
		str = str.substr(str.find(',') + 1);

		airport.latitude = stod(str.substr(0, str.find(',')));

		str = str.substr(str.find(',') + 1);

		airport.longitude = stod(str.substr(0, str.find(',')));

		airports.push_back(airport);
	}
	return true;
}
