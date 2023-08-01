#pragma once

struct Airport {
	char name[30]{};
	double latitude = 0;
	double longitude = 0;
};
struct Flight {
	char from[30]{};
	char to[30]{};
	unsigned int distance = 0;
};

class Data
{
	std::vector<Airport> airports;

public:
	bool open(std::string filename);

};

