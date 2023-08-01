//#include "gui.h"
#include "Graph.h"
#include "Data.h"
#include <iostream>

int main() {

	// Still want GUI?
	//window();

	//int mode = 0;
	//cin >> mode;

	//if (mode == 1){}
	Data d;
	d.openRaw("data\\data");
	d.randomizeFlights(10);
	d.printFlights();

	//Graph g;
	//g.insert("A", "B", 10);
	//g.insert("B", "C", 30);
	//g.insert("A", "C", 60);
	//g.insert("C", "D", 5);

	//vector<string> ans;

	//// Should be: A C D
	//ans = g.findShortestPath_BFS("A", "D");
	//for (string str : ans) {
	//	std::cout << str << " ";
	//}
	//std::cout << std::endl;

	//// Should be: A B C D
	//ans = g.findShortestPath_Astar("A", "D");
	//for (string str : ans) {
	//	std::cout << str << " ";
	//}
	//std::cout << std::endl;

	//// Should be: A B C D
	//ans = g.findShortestPath_Dijkstra("A", "D");
	//for (string str : ans) {
	//	std::cout << str << " ";
	//}
	//std::cout << std::endl;


}