#include <vector>
#include <string>
#include <math.h>

#include "AirportNodes.h"

AirportNodes::AirportNodes() { setX(0); setY(0); setName(""); }
AirportNodes::AirportNodes(float x, float y, std::string name) {
    setX(x);
    setY(y);
    setName(name);
}

AirportNodes::AirportNodes(AirportNodes* node)
{
    /* copy properties, except the neighbors */
    setX(node->x());
    setY(node->y());
    setName(node->name());
}

float AirportNodes::x() { return _x; }
float AirportNodes::y() { return _y; }
std::string AirportNodes::name() { return airport_name; }
void AirportNodes::setX(float x) { _x = x; }
void AirportNodes::setY(float y) { _y = y; }
void AirportNodes::setName(std::string name) { airport_name = name; }
void AirportNodes::addNeighbor(AirportNodes* node)
{
    // Add neighbor node to this->_neighbors if not exist,
    // and add this to the neighbor node->_neighbors
    for (AirportNodes* neighbor : _neighbors)
        if (neighbor == node) return;
    _neighbors.push_back(node);
    node->addNeighbor(this);
}

std::vector<AirportNodes*> AirportNodes::neighbors() { return _neighbors; }

float AirportNodes::distance(AirportNodes* neighbor)
{
    return sqrt(pow(_x - neighbor->x(), 2) + pow(_y - neighbor->y(), 2));
}
