#pragma once

struct Airport {
	char name[30]{};
	double latitude = 0;
	double longitude = 0;
};
struct Flight {
	int from_id = -1;
	int to_id = -1;
	unsigned int distance = 0;
};

class Data
{
public:
	std::vector<Airport> airports;
	std::vector<Flight> flights;

	double toRadians(const double& degree);
	unsigned int distance(double lat1, double long1, double lat2, double long2);


	
	bool openRaw(std::string filename);
	void randomizeFlights(int num);

	void printFlights();
};

