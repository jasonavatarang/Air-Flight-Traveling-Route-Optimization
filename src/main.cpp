#include "gui.h"
#include "Graph.h"

#include <iostream>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {

	//window();

	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	Graph g;
	g.insert("A", "B", 10);
	g.insert("B", "C", 30);
	g.insert("A", "C", 60);
	g.insert("C", "D", 5);

	std::pair<vector<string>, double> ans;
/*
	// Should be: A C D
	ans = g.findShortestPath_BFS("A", "D");
	for (string str : ans) {
		std::cout << str << " ";
	}
	std::cout << std::endl;
*/


	// Should be: A B C D
	ans = g.findShortestPath_Astar("A", "D");
	for (string str : ans.first) {
		std::cout << str << " ";
	}
	std::cout << std::endl;

	// Should be: A B C D
	ans = g.findShortestPath_Dijkstra("A", "D");
	for (string str : ans.first) {
		std::cout << str << " ";
	}
	std::cout << std::endl;

	while (true) {
		Sleep(10000);
	}

}
