#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <utility>
#include <chrono>
#include <cmath>

using namespace std;
class Graph
{
private:
	int size = 0;

	// id
	unordered_map<string, int> ids;
	vector<string> names;
	unordered_map <string, string> flights;

	// adjacency list
	vector<vector<pair<int, int>>> adj_list; // adj_list<id, weight>
	double toRadians(const double& degree);
	int distance(double lat1, double long1, double lat2, double long2);
	void add(string element);
	vector<string> reconstruct_path(int start, int goal, unordered_map<int, int> came_from);
public:
	unordered_map <string, pair<double,double>> airportCoordinates;
	void insert(string from, string to, int weight);
	vector<string> findShortestPath_BFS(string from, string to);
	std::pair<vector<string>, double> findShortestPath_Astar(string from, string to);
	std::pair<vector<string>, double> findShortestPath_Dijkstra(string from, string to);
};    