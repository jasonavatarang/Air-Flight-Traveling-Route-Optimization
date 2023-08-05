#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include <corecrt_math_defines.h>
#include "Data.h"

using namespace std;

// Open raw dataset
bool Data::openRaw(string filename)
{
	ifstream fin(filename, ifstream::in);
	if (!fin.good())
		return false;

	while (fin.good()) {
		int count = 0;
		Airport airport;
		string str;
		string delim = "\",";
		getline(fin, str);

		if (str.size() < 4)
			continue;

		str = str.substr(str.find(',') + 2);

		airport.name = str.substr(0, str.find(delim));

		str = str.substr(str.find(delim) + 2);
		str = str.substr(str.find(delim) + 2);
		str = str.substr(str.find(delim) + 2);
		str = str.substr(str.find(',') + 2);

		airport.name += ", " + str.substr(0, str.find(delim));

		str = str.substr(str.find(delim) + 2);

		airport.latitude = stold(str.substr(0, str.find(',')));

		str = str.substr(str.find(',') + 1);

		airport.longitude = stold(str.substr(0, str.find(',')));

		airports.push_back(airport);
	}
	return true;
}

// Randomize flights, namely edges
void Data::randomizeFlights(unsigned int num)
{
	if (airports.size() == 0)
		return;

	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<mt19937::result_type> dist(0, airports.size() - 1);

	unsigned int outdegree = num / airports.size() + 1;

	for (unsigned int i = 0; i < airports.size(); ++i) {
		for (unsigned int j = 0; j < outdegree; ++j) {
			Flight flight;
			flight.from_id = i;
			flight.to_id = dist(rng);
			if (flight.from_id == flight.to_id)
				continue;

			flights.push_back(flight);
		}
	}
}

// Print all flights
void Data::printFlights()
{
	for (Flight& f : flights)
		cout << airports[f.from_id].name << " -> " << airports[f.to_id].name << endl;
}
