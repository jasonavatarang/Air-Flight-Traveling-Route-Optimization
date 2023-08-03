#include <iostream>
#include "SFML/Graphics.hpp"
#pragma comment(lib, "SFML/lib/sfml-graphics.lib")
#pragma comment(lib, "SFML/lib/sfml-window.lib")
#pragma comment(lib, "SFML/lib/sfml-system.lib")

#include "Graph.h"

using namespace std;

int main()
{

	// Build our own dataset (Run only once)
	
	//Data d;
	//d.openRaw("data/openflights_airports");
	//d.randomizeFlights(500000);

	//Graph g;
	//g.insert(d);

	//g.exportGraph("data/ourDataSet");


	// Read from our own dataset

	Graph g;
	g.importGraph("data/ourDataSet");


	vector <string> ans;
	unsigned int cost, time;

	string from = "Yaoqiang Airport";
	string to = "John F Kennedy International Airport";

	//string from, to;
	//from = g.getValidAirportName("Please enter your initial airport location (from): ");
	//to = g.getValidAirportName("Please enter your airport destination (to): ");

	cout << "\nDisplacement: " << from << " -> " << to << endl;
	cout << g.Displacement(from, to) << " km\n\n";


	//cout << "BFS:\n";
	//ans = g.BFS("Madang", "Thule", cost, time);
	//if (ans.size() == 0)
	//	cout << "No path\n";
	//for (string str : ans) {
	//	cout << str << " -> ";
	//}
	//cout << "ARRIVED\n";
	//cout << "Distance: " << cost << " km\n";
	//cout << "Used time: " << time << " microsec\n\n";


	cout << "Dijkstra:\n";
	ans = g.Dijkstra(from, to, cost, time);
	if (ans.size() == 0)
		cout << "No path\n";
	for (string str : ans) {
		cout << str << " -> ";
	}
	cout << "ARRIVED\n";
	cout << "Distance: " << cost << " km\n";
	cout << "Used time: " << time << " microsec\n\n";


	cout << "Astar:\n";
	ans = g.Astar(from, to, cost, time);
	if (ans.size() == 0)
		cout << "No path\n";
	for (string str : ans) {
		cout << str << " -> ";
	}
	cout << "ARRIVED\n";
	cout << "Distance: " << cost << " km\n";
	cout << "Used time: " << time << " microsec\n\n";





}