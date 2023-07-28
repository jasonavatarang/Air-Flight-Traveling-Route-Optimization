#include "Graph.h"

#include <iostream>

// Initialize one single node
void Graph::add(string element)
{
	if (ids.find(element) != ids.end())
		return;
	ids[element] = size;
	names.push_back(element);
	adj_list.push_back({});
	size++;
}

// Output path from unordered map
vector<string> Graph::reconstruct_path(int start, int to, unordered_map<int, int> came_from) {
	vector<string> path;
	int current = to;
	if (came_from.find(to) == came_from.end())
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
	/*
	
	  PriorityQueue<Location, double> frontier;
  frontier.put(start, 0);

  came_from[start] = start;
  cost_so_far[start] = 0;
  
  while (!frontier.empty()) {
    Location current = frontier.get();

    if (current == goal) {
      break;
    }

    for (Location next : graph.neighbors(current)) {
      double new_cost = cost_so_far[current] + graph.cost(current, next);
      if (cost_so_far.find(next) == cost_so_far.end()
          || new_cost < cost_so_far[next]) {
        cost_so_far[next] = new_cost;
        double priority = new_cost + heuristic(next, goal);
        frontier.put(next, priority);
        came_from[next] = current;
      }
    }
  }
	*/
	auto start = std::chrono::high_resolution_clock::now();

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > frontier;
	frontier.push(make_pair(ids[from], INT_MAX));

	unordered_map<int, int> came_from;
	unordered_map<int, int> cost_so_far;
	came_from[ids[from]] = ids[from];
	cost_so_far[ids[from]] = 0;

	while (!frontier.empty()) {
		int current = frontier.top().first;
		frontier.pop();
		if (names[current] == to) {
			break;
		}
		for (pair<int, int> next : adj_list[current]) {
			int new_cost = cost_so_far[current] + next.second;
			if (cost_so_far.find(next.first) == cost_so_far.end()
				|| new_cost < cost_so_far[next.first]) {
				cost_so_far[next.first] = new_cost;
				int priority = new_cost;
				frontier.push(make_pair(next.first, priority));
				came_from[next.first] = current;
			}
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << "Time Computation: " << diff.count() * 1000.0 << endl;
	return reconstruct_path(ids[from], ids[to], came_from);
}

vector<string> Graph::findShortestPath_Dijkstra(string from, string to)
{

	/*
	 PriorityQueue<Location, double> frontier;
  frontier.put(start, 0);

  came_from[start] = start;
  cost_so_far[start] = 0;
  
  while (!frontier.empty()) {
    Location current = frontier.get();

    if (current == goal) {
      break;
    }

    for (Location next : graph.neighbors(current)) {
      double new_cost = cost_so_far[current] + graph.cost(current, next);
      if (cost_so_far.find(next) == cost_so_far.end()
          || new_cost < cost_so_far[next]) {
        cost_so_far[next] = new_cost;
        came_from[next] = current;
        frontier.put(next, new_cost);
      }
    }
  }
}
	*/
	auto start = std::chrono::high_resolution_clock::now();

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > frontier;
	frontier.push(make_pair(ids[from], INT_MAX));

	unordered_map<int, int> came_from;
	unordered_map<int, int> cost_so_far;
	came_from[ids[from]] = ids[from];
	cost_so_far[ids[from]] = 0;

	while (!frontier.empty()) {
		int current = frontier.top().first;
		frontier.pop();
		if (names[current] == to) {
			break;
		}
		for (pair<int, int> next : adj_list[current]) {
			int new_cost = cost_so_far[current] + next.second;
			if (cost_so_far.find(next.first) == cost_so_far.end()
				|| new_cost < cost_so_far[next.first]) {
				cost_so_far[next.first] = new_cost;
				came_from[next.first] = current;
				frontier.push(make_pair(next.first, new_cost));
			}
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << "Time Computation: " << diff.count() * 1000.0 << endl;
	return reconstruct_path(ids[from], ids[to], came_from);
}
