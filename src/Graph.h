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
	std::vector<std::pair<double, double>> coordinates; // coordinates<latitude, longitude>

	double toRadians(const double& degree);
	unsigned int GCdistance(double lat1, double long1, double lat2, double long2);

	void add(std::string& element, double& lat, double& lon);
	std::vector<std::string> reconstruct_path(int start, int to, std::vector<int>& came_from);

public:
	// Modifiers
	void insert(std::string from, std::string to, unsigned int weight, double lat1, double long1, double lat2, double long2);
	void insert(Data& data);

	// Export & Import
	bool exportGraph(std::string filename);
	bool importGraph(std::string filename);	

	// Observers
	bool search(std::string& airport);
	std::pair<double, double> getCoordinates(std::string& airport);

	// Path algms
	unsigned int Displacement(std::string& from, std::string& to);
	std::vector<std::string> BFS(std::string& from, std::string& to, unsigned int& cost);
	std::vector<std::string> BFS(std::string& from, std::string& to, unsigned int& cost, unsigned int& time);
	std::vector<std::string> Astar(std::string& from, std::string& to, unsigned int& cost);
	std::vector<std::string> Astar(std::string& from, std::string& to, unsigned int& cost, unsigned int& time);
	std::vector<std::string> Dijkstra(std::string& from, std::string& to, unsigned int& cost);
	std::vector<std::string> Dijkstra(std::string& from, std::string& to, unsigned int& cost, unsigned int& time);
};