#ifndef AIRPORTNODES_H
#define AIRPORTNODES_H

class AirportNodes {
private:
	float x;
	float y;
	std::string airport_name;
public:
	AirportNodes(float x, float y, std::string airport_name);
};

#endif