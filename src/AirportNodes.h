#ifndef AIRPORTNODES_H
#define AIRPORTNODES_H

class AirportNodes {
private:
	float _x;
	float _y;
	std::string airport_name;
    std::vector<AirportNodes*> _neighbors;
public:
    AirportNodes();
	AirportNodes(float x, float y, std::string airport_name);
    AirportNodes(AirportNodes* node);
    float x();
    float y();
    std::string name();
    void setX(float x);
    void setY(float y);
    void setName(std::string name);
    void addNeighbor(AirportNodes* node);
    std::vector<AirportNodes*> neighbors();
    float distance(AirportNodes* neighbor);


};

#endif