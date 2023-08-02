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
	long double one_deg = (M_PI) / 180;
	return (one_deg * degree);
}

unsigned int Data::GCdistance(double lat1, double long1, double lat2, double long2)
{
	// Convert the latitudes and longitudes from degree to radians
	lat1 = toRadians(lat1);
	long1 = toRadians(long1);
	lat2 = toRadians(lat2);
	long2 = toRadians(long2);

	// Haversine Formula
	long double dlong = long2 - long1;
	long double dlat = lat2 - lat1;

	long double ans = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2);

	ans = 2 * asin(sqrt(ans));

	// Radius of Earth, R = 6371 km OR 3956 miles
	long double R = 6371;

	return ans * R;
}

bool Data::openRaw(string filename)
{
	ifstream fin(filename, ifstream::in);
	if (!fin.good())
		return false;

	while (fin.good()) {
		int count = 0;
		Airport airport;
		string str;
		getline(fin, str);

		if (str.size() < 4)
			continue;

		str = str.substr(str.find(',') + 2);
		while (str[0] != ',')
			str = str.substr(str.find('"') + 1);
		str = str.substr(str.find('"') + 1);

		airport.name = str.substr(0, str.find('"'));
		str = str.substr(str.find('"') + 2);

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

void Data::printFlights()
{
	for (Flight& f : flights)
		cout << airports[f.from_id].name << " -> " << airports[f.to_id].name << " : " << f.distance << endl;
}
