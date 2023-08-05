#pragma once

class Data
{
	struct Airport {
		std::string name;
		double latitude = 0;
		double longitude = 0;
	};
	struct Flight {
		int from_id = -1;
		int to_id = -1;
	};

public:
	std::vector<Airport> airports;
	std::vector<Flight> flights;

	bool openRaw(std::string filename);
	void randomizeFlights(int num);

	void printFlights();
};

