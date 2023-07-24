#include "Graph.h"

// Initialize one single node
void Graph::add(string element)
{
	if (ids.find(element) != ids.end())
		return;
	ids[element] = size;
	adj_list.push_back({});
	size++;
}

// Output path from unordered map
vector<string> Graph::reconstruct_path(int start, int goal, unordered_map<int, int> came_from) {
	vector<string> path;
	int current = goal;
	if (came_from.find(goal) == came_from.end())
		return path;

	while (current != start) {
		path.push_back(names[current]);
		current = came_from[current];
	}

	path.push_back(names[start]);
	reverse(path.begin(), path.end());
	return path;
}

// Insert an edge to the graph
void Graph::insert(string from, string to, int weight)
{
	add(from);
	add(to);
	adj_list[ids[from]].push_back(make_pair(ids[to], weight));
}

// Breadth First Search
vector<string> Graph::findShortestPath_BFS(string from, string to)
{
	queue<int> frontier;
	frontier.push(ids[from]);

	unordered_map<int, int> came_from;
	came_from[ids[from]] = ids[from];

	while (!frontier.empty()) {
		int current = frontier.front();
		frontier.pop();

		if (current == ids[to])
			break;

		for (pair<int, int> next : adj_list[current]) {
			if (came_from.find(next.first) == came_from.end()) {
				frontier.push(next.first);
				came_from[next.first] = current;
			}
		}
	}
	return reconstruct_path(ids[from], ids[to], came_from);
}

vector<string> Graph::findShortestPath_Astar(string from, string to)
{
	return vector<string>();
}

vector<string> Graph::findShortestPath_Dijkstra(string from, string to)
{
	return vector<string>();
}
