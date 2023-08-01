#pragma once

class Data
{
	struct flight {
		char from[30]{};
		char to[30]{};
		unsigned int distance = 0;
	};
	struct airport {
		char name[30]{};
		double latitude = 0;
		double longitude = 0;
	};

	std::vector<airport> airports;

public:
	bool open(char* filename);

};

