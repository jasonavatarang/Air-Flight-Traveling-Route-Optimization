#pragma comment(lib, "SFML/lib/sfml-graphics.lib")
#pragma comment(lib, "SFML/lib/sfml-window.lib")
#pragma comment(lib, "SFML/lib/sfml-system.lib")
#include <iostream>
#include "Graph.h"
#include "Display.h"

int main()
{
	Graph g;

	int mode = 0;
	std::cout << "User Mode:\n1: Open raw dataset and randomly generate a graph;\n2: Open the graph and prompt window;\n";
	std::cin >> mode;
	if (mode == 1) {
		Data d;
		d.openRaw("data/openflights_airports");
		d.randomizeFlights(1000000);

		g.insert(d);
		g.exportGraph("data/ourDataSet");
	}
	else if (mode == 2) {
		g.importGraph("data/ourDataSet");
		PromptWindow(g);
	}
}
