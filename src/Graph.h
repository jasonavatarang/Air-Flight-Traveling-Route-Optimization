#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

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

	void add(string element);
	vector<string> reconstruct_path(int start, int goal, unordered_map<int, int> came_from);

public:
	void insert(string from, string to, int weight);
	vector<string> findShortestPath_BFS(string from, string to);
	vector<string> findShortestPath_Astar(string from, string to);
	vector<string> findShortestPath_Dijkstra(string from, string to);
};

