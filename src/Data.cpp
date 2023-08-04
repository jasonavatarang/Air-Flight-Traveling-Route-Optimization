#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include <corecrt_math_defines.h>
#include "Data.h"

using namespace std;

double Data::toRadians(const double& degree)
{
	return degree * M_PI / 180.0;
}

// Calculate great-circle distance
unsigned int Data::GCdistance(double lat1, double lon1, double lat2, double lon2)
{
	lat1 = toRadians(lat1);
	lon1 = toRadians(lon1);
	lat2 = toRadians(lat2);
	lon2 = toRadians(lon2);

	// Haversine Formula
	double dlat = abs(lat1 - lat2);
	double dlon = abs(lon1 - lon2);
	double ans = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
	ans = 2 * asin(sqrt(ans));

	// Radius of Earth, R = 6371 km OR 3956 miles
	double R = 6371;

	return ans * R;
}

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

// Randomize flights, namely edges
void Data::randomizeFlights(int num)
{
	if (airports.size() == 0)
		return;

	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<mt19937::result_type> dist(0, airports.size() - 1);

	while (num > 0) {
		Flight flight;
		flight.from_id = dist(rng);
		flight.to_id = dist(rng);
		if (flight.from_id == flight.to_id)
			continue;

		flight.distance = GCdistance(airports[flight.from_id].latitude, airports[flight.from_id].longitude, airports[flight.to_id].latitude, airports[flight.to_id].longitude);
		flights.push_back(flight);
		--num;
	}
}

// Print all flights
void Data::printFlights()
{
	for (Flight& f : flights)
		cout << airports[f.from_id].name << " -> " << airports[f.to_id].name << " : " << f.distance << endl;
}
