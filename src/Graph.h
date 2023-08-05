#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "Data.h"

class Graph
{
private:
	int size = 0;

	// id
	std::unordered_map<std::string, int> ids;
	std::vector<std::string> names;

	// adjacency list
	std::vector<std::vector<std::pair<int, unsigned int>>> adj_list; // adj_list<id, weight>

	// coordinates
	std::vector<std::pair<long double, long double>> coordinates; // coordinates<latitude, longitude>

	void toRadians(long double& degree);
	unsigned int GCdistance(long double lat1, long double lon1, long double lat2, long double lon2);

	void add(std::string& element, long double& lat, long double& lon);
	std::vector<std::string> reconstruct_path(int start, int to, std::vector<int>& came_from);

public:
	// Modifiers
	void insert(std::string from, std::string to, unsigned int weight, long double lat1, long double long1, long double lat2, long double long2);
	void insert(Data& data);

	// Export & Import
	bool exportGraph(std::string filename);
	bool importGraph(std::string filename);	

	// Observers
	bool search(std::string& airport);
	std::pair<long double, long double> getCoordinates(const std::string& airport);

	// Path algms
	unsigned int Displacement(std::string& from, std::string& to);
	std::vector<std::string> BFS(std::string& from, std::string& to, unsigned int& cost);
	std::vector<std::string> BFS(std::string& from, std::string& to, unsigned int& cost, unsigned int& time);
	std::vector<std::string> Astar(std::string& from, std::string& to, unsigned int& cost);
	std::vector<std::string> Astar(std::string& from, std::string& to, unsigned int& cost, unsigned int& time);
	std::vector<std::string> Dijkstra(std::string& from, std::string& to, unsigned int& cost);
	std::vector<std::string> Dijkstra(std::string& from, std::string& to, unsigned int& cost, unsigned int& time);
};