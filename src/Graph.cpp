#include <queue>
#include <iostream>
#include <chrono>
#include <corecrt_math_defines.h>

#include "Graph.h"

using namespace std;

double Graph::toRadians(const double& degree)
{
	long double one_deg = (M_PI) / 180;
	return (one_deg * degree);
}

unsigned int Graph::distance(double lat1, double lon1, double lat2, double lon2)
{
	// Convert the latitudes and longitudes from degree to radians
	lat1 = toRadians(lat1);
	lon1 = toRadians(lon1);
	lat2 = toRadians(lat2);
	lon2 = toRadians(lon2);

	// Haversine Formula
	long double dlong = lon2 - lon1;
	long double dlat = lat2 - lat1;

	long double ans = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2);

	ans = 2 * asin(sqrt(ans));

	// Radius of Earth, R = 6371 km OR 3956 miles
	long double R = 6371;

	return ans * R;
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

vector<string> Graph::BFS(string from, string to, unsigned int& cost)
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

vector<string> Graph::BFS(string from, string to, unsigned int& cost, unsigned int& time)
{
	auto start = chrono::steady_clock::now();

	vector<string> result = BFS(from, to, cost);

	auto stop = chrono::steady_clock::now();
	auto duration = chrono::duration_cast <chrono::microseconds> (stop - start);
	time = duration.count();

	return result;
}


vector<string> Graph::Astar(string from, string to)
{
	return vector<string>();
	//auto start = chrono::high_resolution_clock::now();

	//priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > frontier;
	//frontier.push(make_pair(ids[from], INT_MAX));

	//unordered_map<int, int> came_from;
	//unordered_map<int, int> cost_so_far;
	//came_from[ids[from]] = ids[from];
	//cost_so_far[ids[from]] = 0;

	//while (!frontier.empty()) {
	//	int current = frontier.top().first;
	//	frontier.pop();
	//	if (names[current] == to) {
	//		break;
	//	}
	//	
	//	for (pair<int, int> next : adj_list[current]) {
	//		int new_cost = cost_so_far[current] + next.second;
	//		if (cost_so_far.find(next.first) == cost_so_far.end() || new_cost < cost_so_far[next.first]) {
	//			cost_so_far[next.first] = new_cost;
	//			int priority = new_cost + abs(distance(airportCoordinates[from].first, airportCoordinates[from].second, airportCoordinates[to].first, airportCoordinates[to].second)); // heuristic formula: haversine
	//			frontier.push(make_pair(next.first, priority));
	//			came_from[next.first] = current;
	//		}
	//	}
	//}
	//auto end = chrono::high_resolution_clock::now();
	//chrono::duration<double> diff = end - start;
	//double time = diff.count() * 1000.0;
	//cout << "Time Computation (ms): " << time << endl;
	//return reconstruct_path(ids[from], ids[to], came_from);
}

vector<string> Graph::Dijkstra(string from, string to, unsigned int& cost)
{
	// pq<weight, node_id> ordered by the first element
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
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
			}
			if (!visited[next.first])
				pq.emplace(cost_so_far[next.first], next.first);
		}
	}
	cost = cost_so_far[ids[to]];
	return reconstruct_path(ids[from], ids[to], came_from);
}

vector<string> Graph::Dijkstra(string from, string to, unsigned int& cost, unsigned int& time)
{
	auto start = chrono::steady_clock::now();

	vector<string> result = Dijkstra(from, to, cost);

	auto stop = chrono::steady_clock::now();
	auto duration = chrono::duration_cast <chrono::microseconds> (stop - start);
	time = duration.count();

	return result;
}
