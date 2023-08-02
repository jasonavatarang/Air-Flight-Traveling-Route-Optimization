#include <iostream>

//#include "gui.h"
#include "Graph.h"

using namespace std;

int main()
{
	Data d;
	d.openRaw("data\\openflights_airports");
	d.randomizeFlights(50000);
	//d.printFlights();

	Graph g;
	g.insert(d);

	vector <string> ans;
	unsigned int cost;
	unsigned int time;


	cout << "BFS:\n";
	ans = g.BFS("Madang", "Thule", cost, time);
	if (ans.size() == 0)
		cout << "No path\n";
	for (string str : ans) {
		cout << str << " -> ";
	}
	cout << "ARRIVED\n";
	cout << "Distance: " << cost << " km\n";
	cout << "Used time: " << time << " ms\n\n";


	cout << "Dijkstra:\n";
	ans = g.Dijkstra("Madang", "Thule", cost, time);
	if (ans.size() == 0)
		cout << "No path\n";
	for (string str : ans) {
		cout << str << " -> ";
	}
	cout << "ARRIVED\n";
	cout << "Distance: " << cost << " km\n";
	cout << "Used time: " << time << " ms\n\n";


	cout << "Astar:\n";
	ans = g.Astar("Madang", "Thule", cost, time);
	if (ans.size() == 0)
		cout << "No path\n";
	for (string str : ans) {
		cout << str << " -> ";
	}
	cout << "ARRIVED\n";
	cout << "Distance: " << cost << " km\n";
	cout << "Used time: " << time << " ms\n\n";







	// Still want GUI?
	//window();

	//int mode = 0;
	//cin >> mode;

}