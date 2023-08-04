#pragma comment(lib, "SFML/lib/sfml-graphics.lib")
#pragma comment(lib, "SFML/lib/sfml-window.lib")
#pragma comment(lib, "SFML/lib/sfml-system.lib")
#include "SFML/Graphics.hpp"
#include "Graph.h"
#include "Display.h"

int main()
{
	Graph g;
	g.importGraph("data/ourDataSet");


	PromptWindow(g);








	//unsigned int cost, time;

	//string from = "Yaoqiang Airport";
	//string to = "John F Kennedy International Airport";
	////string from, to;
	////from = g.getValidAirportName("Please enter your initial airport location (from): ");
	////to = g.getValidAirportName("Please enter your airport destination (to): ");
	//cout << endl;
	//cout << "Displacement: " << from << " -> " << to << "\n";
	//cout << g.Displacement(from, to) << " km\n\n";

	//cout << "Dijkstra:\n";
	//vector <string> dijskstra_ans = g.Dijkstra(from, to, cost, time);
	//if (dijskstra_ans.size() == 0)
	//	cout << "No path\n";
	//for (string str : dijskstra_ans) {
	//	cout << str << " -> ";
	//}
	//cout << "ARRIVED\n";
	//cout << "Distance: " << cost << " km\n";
	//cout << "Used time: " << time << " microsec\n\n";



	//cout << "Astar:\n";
	//vector <string> Astar_ans = g.Astar(from, to, cost, time);
	//if (Astar_ans.size() == 0)
	//	cout << "No path\n";
	//for (string str : Astar_ans) {
	//	cout << str << " -> ";
	//}
	//cout << "ARRIVED\n";
	//cout << "Distance: " << cost << " km\n";
	//cout << "Used time: " << time << " microsec\n\n";

}

