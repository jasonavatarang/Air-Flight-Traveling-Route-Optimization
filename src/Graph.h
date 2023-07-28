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

	// adjacency list
	vector<vector<pair<int, int>>> adj_list; // adj_list<id, weight>
	long double toRadians(const long double& degree);
	long double distance(long double lat1, long double long1,
		long double lat2, long double long2);
	void add(string element);
	vector<string> reconstruct_path(int start, int goal, unordered_map<int, int> came_from);

public:
	void insert(string from, string to, int weight);
	vector<string> findShortestPath_BFS(string from, string to);
	std::pair<vector<string>, double> findShortestPath_Astar(string from, string to);
	std::pair<vector<string>, double> findShortestPath_Dijkstra(string from, string to);
};

