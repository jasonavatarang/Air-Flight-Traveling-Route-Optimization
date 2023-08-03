#include <iostream>
#include "SFML/Graphics.hpp"
#pragma comment(lib, "SFML/lib/sfml-graphics.lib")
#pragma comment(lib, "SFML/lib/sfml-window.lib")
#pragma comment(lib, "SFML/lib/sfml-system.lib")
#include "Graph.h"
#include "AirportNodes.h"
#include <string>

using namespace std;

int main()
{

	int width = 800;
	int height = 600;
	int number_nodes;

	Data d;
	d.openRaw("data\\openflights_airports");
	d.randomizeFlights(500000);

	vector <string> ans;
	unsigned int cost;
	unsigned int time;

	//string from = "Yaoqiang Airport";
	//string to = "John F Kennedy International Airport";
	string from, to;
	from = g.getValidAirportName("Please enter your initial airport location (from): ");
	to = g.getValidAirportName("Please enter your airport destination (to): ");
	cout << endl;
	cout << "Displacement: " << from << " -> " << to << "\n";
	cout << g.Displacement(from, to) << " km\n\n";

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

	sf::CircleShape nodeCircles[number_nodes];

	for (int i = 0; i < n_nodes; ++i)
	{
		float radius = 10;
		nodeCircles[i].setRadius(radius);
		nodeCircles[i].setPosition(sf::Vector2f(nodeList[i]->x() - radius, nodeList[i]->y() - radius));
		nodeCircles[i].setFillColor(sf::Color(0, 0, 0, 30));
	}

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(width, height), "Graph", sf::Style::Default, settings);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color::White);
		for (int i = 0; i < n_nodes; ++i)
		{
			window.draw(nodeCircles[i]);
			for (Node* neighbor : nodeList[i]->neighbors())
			{
				sf::RectangleShape line = Line(nodeList[i]->x(), nodeList[i]->y(), neighbor->x(), neighbor->y());
				window.draw(line);
			}
		}

		window.display();
	}

	/*Data d;
	d.openRaw("data\\openflights_airports");
	d.randomizeFlights(500000);

	Graph g;
	g.insert(d);

	vector <string> ans;
	unsigned int cost, time;

	//string from = "Yaoqiang Airport";
	//string to = "John F Kennedy International Airport";
	string from, to;
	from = g.getValidAirportName("Please enter your initial airport location (from): ");
	to = g.getValidAirportName("Please enter your airport destination (to): ");
	cout << endl;
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
	

}*/

