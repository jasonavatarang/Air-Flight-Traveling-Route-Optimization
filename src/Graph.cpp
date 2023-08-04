#include <queue>
#include <iostream>
#include <chrono>
#include <fstream>
#include <corecrt_math_defines.h>
#include "Graph.h"

using namespace std;

// Degrees to Radians
double Graph::toRadians(const double& degree)
{
	return degree * M_PI / 180.0;
}

// Calculate great-circle distance
unsigned int Graph::GCdistance(double lat1, double lon1, double lat2, double lon2)
{
	lat1 = toRadians(lat1);
	lon1 = toRadians(lon1);
	lat2 = toRadians(lat2);
	lon2 = toRadians(lon2);

	// Haversine Formula
	double dlat = abs(lat1 - lat2);
	double dlon = abs(lon1 - lon2);
	double ans = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
	ans = 2 * asin(sqrt(ans));

	// Radius of Earth, R = 6371 km OR 3956 miles
	double R = 6371;

	return ans * R;
}

// Search for airport name
bool Graph::search(string& airport) {
	return ids.find(airport) != ids.end();
}

// Return coordinates of an airport
pair<double, double> Graph::getCoordinates(string& airport)
{
	return coordinates[ids[airport]];
}

// Initialize one single node
void Graph::add(string& element, double& lat, double& lon)
{
	if (ids.find(element) != ids.end())
		return;
	ids[element] = size;
	names.push_back(element);
	adj_list.emplace_back();
	coordinates.emplace_back(lat, lon);
	size++;
}

// Output the path
vector<string> Graph::reconstruct_path(int start, int to, vector<int>& came_from) {
	vector<string> path;
	int current = to;
	if (came_from[to] == -1)
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
void Graph::insert(string from, string to, unsigned int weight, double lat1, double lon1, double lat2, double lon2)
{
	// Initialize
	add(from, lat1, lon1);
	add(to, lat2, lon2);

	// Check duplicate
	for (auto& node : adj_list[ids[from]])
		if (node.first == ids[to])
			return;

	adj_list[ids[from]].emplace_back(ids[to], weight);
}

// Insert Data obejct to the graph
void Graph::insert(Data& data)
{
	for (int i = 0; i < data.flights.size(); ++i)
		insert(string(data.airports[data.flights[i].from_id].name), string(data.airports[data.flights[i].to_id].name),
			data.flights[i].distance,
			data.airports[data.flights[i].from_id].latitude, data.airports[data.flights[i].from_id].longitude,
			data.airports[data.flights[i].to_id].latitude, data.airports[data.flights[i].to_id].longitude);
}

// Export graph itself
bool Graph::exportGraph(std::string filename)
{
	ofstream fout(filename, ios::binary);
	if (!fout.is_open())
		return false;

	// write size
	fout.write((char*)&size, sizeof(size));

	// write names
	for (string& name : names) {
		unsigned short n_size = name.size() + 1;
		fout.write((char*)&n_size, sizeof(n_size));
		fout.write(name.c_str(), n_size);
	}
	// write adj_list
	for (vector<pair<int, unsigned int>>& edges : adj_list) {
		unsigned short v_size = edges.size();
		fout.write((char*)&v_size, sizeof(v_size));
		for (pair<int, unsigned int>& e : edges)
			fout.write((char*)&e, sizeof(e));
	}
	// write coordinates
	for (pair<double, double>& coord : coordinates)
		fout.write((char*)&coord, sizeof(coord));

	fout.close();
	return true;
}

// Import graph itself
bool Graph::importGraph(std::string filename)
{
	ifstream fin(filename, ios::binary);
	if (!fin.is_open())
		return false;

	// read size
	fin.read((char*)&size, sizeof(size));

	// read names
	for (int i = 0; i < size;++i) {
		unsigned short n_size;
		fin.read((char*)&n_size, sizeof(n_size));
		char* name = new char[n_size];
		fin.read(name, n_size);
		names.emplace_back(name);
		delete[] name;
	}
	// read adj_list
	for (int i = 0; i < size; ++i) {
		adj_list.emplace_back();

		unsigned short v_size;
		fin.read((char*)&v_size, sizeof(v_size));
		for (int j = 0; j < v_size; ++j) {
			pair<int, unsigned int> e;
			fin.read((char*)&e, sizeof(e));
			adj_list[i].push_back(e);
		}
	}
	// read coordinates
	for (int i = 0; i < size; ++i) {
		pair<double, double> coord;
		fin.read((char*)&coord, sizeof(coord));
		coordinates.push_back(coord);
	}
	// build ids
	for (int i = 0; i < size; ++i)
		ids[names[i]] = i;

	fin.close();
	return true;
}

// Actual distance between two places
unsigned int Graph::Displacement(std::string& from, std::string& to)
{
	return GCdistance(coordinates[ids[from]].first, coordinates[ids[from]].second, coordinates[ids[to]].first, coordinates[ids[to]].second);
}

// Breadth First Search
vector<string> Graph::BFS(string& from, string& to, unsigned int& cost)
{
	queue<int> q;
	vector<int> came_from(size, -1);
	vector<unsigned int> cost_so_far(size, UINT_MAX);
	vector<bool> visited(size, false);

	q.push(ids[from]);

	while (!q.empty()) {
		int current = q.front();
		visited[current] = true;
		q.pop();

		if (current == ids[to]) {
			break;
		}

		for (pair<int, unsigned int>& next : adj_list[current]) {
			if (!visited[next.first]) {
				came_from[next.first] = current;
				cost_so_far[next.first] = cost_so_far[current] + next.second;
				q.push(next.first);
			}
		}
	}
	cost = cost_so_far[ids[to]];
	return reconstruct_path(ids[from], ids[to], came_from);
}

// Breadth First Search with timer
vector<string> Graph::BFS(string& from, string& to, unsigned int& cost, unsigned int& time)
{
	auto start = chrono::steady_clock::now();

	vector<string> result = BFS(from, to, cost);

	auto stop = chrono::steady_clock::now();
	auto duration = chrono::duration_cast <chrono::microseconds> (stop - start);
	time = duration.count();

	return result;
}

// A* Search
vector<string> Graph::Astar(string& from, string& to, unsigned int& cost)
{
	// pq<weight, node_id> ordered by the first element
	priority_queue<pair<unsigned int, int>, vector<pair<unsigned int, int>>, greater<pair<unsigned int, int>>> pq;
	vector<int> came_from(size, -1);
	vector<unsigned int> cost_so_far(size, UINT_MAX);
	vector<bool> visited(size, false);

	pair<double, double> dest_coordinates(coordinates[ids[to]].first, coordinates[ids[to]].second);

	cost_so_far[ids[from]] = 0;
	pq.emplace(cost_so_far[ids[from]], ids[from]);

	while (!pq.empty()) {
		int current = pq.top().second;
		visited[current] = true;
		pq.pop();

		if (current == ids[to]) {
			break;
		}

		for (pair<int, unsigned int>& next : adj_list[current]) {
			unsigned int new_cost = cost_so_far[current] + next.second;
			if (new_cost < cost_so_far[next.first]) {
				came_from[next.first] = current;
				cost_so_far[next.first] = new_cost;
				// Heuristic formula: cost_so_far + distance_to_destination
				if (!visited[next.first])
					pq.emplace(cost_so_far[next.first] + GCdistance(coordinates[next.first].first, coordinates[next.first].second, dest_coordinates.first, dest_coordinates.second), next.first);
			}
		}
	}
	cost = cost_so_far[ids[to]];
	return reconstruct_path(ids[from], ids[to], came_from);
}

// A* Search with timer
vector<string> Graph::Astar(string& from, string& to, unsigned int& cost, unsigned int& time)
{
	auto start = chrono::steady_clock::now();

	vector<string> result = Astar(from, to, cost);

	auto stop = chrono::steady_clock::now();
	auto duration = chrono::duration_cast <chrono::microseconds> (stop - start);
	time = duration.count();

	return result;
}

// Dijkstra Search
vector<string> Graph::Dijkstra(string& from, string& to, unsigned int& cost)
{
	// pq<weight, node_id> ordered by the first element
	priority_queue<pair<unsigned int, int>, vector<pair<unsigned int, int>>, greater<pair<unsigned int, int>>> pq;
	vector<int> came_from(size, -1);
	vector<unsigned int> cost_so_far(size, UINT_MAX);
	vector<bool> visited(size, false);

	cost_so_far[ids[from]] = 0;
	pq.emplace(cost_so_far[ids[from]], ids[from]);

	while (!pq.empty()) {
		int current = pq.top().second;
		visited[current] = true;
		pq.pop();

		if (current == ids[to]) {
			break;
		}

		for (pair<int, unsigned int>& next : adj_list[current]) {
			unsigned int new_cost = cost_so_far[current] + next.second;
			if (new_cost < cost_so_far[next.first]) {
				came_from[next.first] = current;
				cost_so_far[next.first] = new_cost;
				if (!visited[next.first])
					pq.emplace(cost_so_far[next.first], next.first);
			}
		}
	}
	cost = cost_so_far[ids[to]];
	return reconstruct_path(ids[from], ids[to], came_from);
}

// Dijkstra Search with timer
vector<string> Graph::Dijkstra(string& from, string& to, unsigned int& cost, unsigned int& time)
{
	auto start = chrono::steady_clock::now();

	vector<string> result = Dijkstra(from, to, cost);

	auto stop = chrono::steady_clock::now();
	auto duration = chrono::duration_cast <chrono::microseconds> (stop - start);
	time = duration.count();

	return result;
}
