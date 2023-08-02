#include <iostream>

//#include "gui.h"
#include "Graph.h"

using namespace std;

int main()
{
	Data d;
	d.openRaw("data\\openflights_airports");
	d.randomizeFlights(500000);

	Graph g;
	g.insert(d);

	vector <string> ans;
	unsigned int cost;
	unsigned int time;

	string from = "Yaoqiang Airport";
	string to = "John F Kennedy International Airport";

	cout << "Displacement: " << from << " -> " << to << "\n";
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







	// Still want GUI?
	//window();

	//int mode = 0;
	//cin >> mode;

}