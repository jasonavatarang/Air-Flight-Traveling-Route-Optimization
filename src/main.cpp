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

	Graph g;
	g.importGraph("data/ourDataSet");

	unsigned int cost, time;

	string from = "Yaoqiang Airport";
	string to = "John F Kennedy International Airport";
	//string from, to;
	//from = g.getValidAirportName("Please enter your initial airport location (from): ");
	//to = g.getValidAirportName("Please enter your airport destination (to): ");
	cout << endl;
	cout << "Displacement: " << from << " -> " << to << "\n";
	cout << g.Displacement(from, to) << " km\n\n";

	cout << "Dijkstra:\n";
	vector <string> dijskstra_ans = g.Dijkstra(from, to, cost, time);
	if (dijskstra_ans.size() == 0)
		cout << "No path\n";
	for (string str : dijskstra_ans) {
		cout << str << " -> ";
	}
	cout << "ARRIVED\n";
	cout << "Distance: " << cost << " km\n";
	cout << "Used time: " << time << " microsec\n\n";



	cout << "Astar:\n";
	vector <string> Astar_ans = g.Astar(from, to, cost, time);
	if (Astar_ans.size() == 0)
		cout << "No path\n";
	for (string str : Astar_ans) {
		cout << str << " -> ";
	}
	cout << "ARRIVED\n";
	cout << "Distance: " << cost << " km\n";
	cout << "Used time: " << time << " microsec\n\n";


	sf::CircleShape* nodeCirclesDijskstra = new sf::CircleShape[dijskstra_ans.size()];
	sf::CircleShape* nodeCirclesAstar = new sf::CircleShape[Astar_ans.size()];

	std::vector<AirportNodes> nodeListDijskstra(dijskstra_ans.size());
	std::vector<AirportNodes> nodeListAstar(Astar_ans.size());

	for (int i = 0; i < dijskstra_ans.size(); ++i) {
		float radius = 10;
		nodeCirclesDijskstra[i].setRadius(radius);
		nodeCirclesDijskstra[i].setPosition(sf::Vector2f(nodeListDijskstra[i].x() - radius, nodeListDijskstra[i].y() - radius));
		nodeCirclesDijskstra[i].setFillColor(sf::Color(0, 0, 0, 30));

		sf::Text label;
		label.setString("Airport: " + dijskstra_ans[i]);
		label.setCharacterSize(12);
		label.setFillColor(sf::Color::Black);
		label.setPosition(sf::Vector2f(nodeListDijskstra[i].x() + 2 * radius, nodeListDijskstra[i].y() - 0.5 * radius));
	}

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(width, height), "Dijskstra Graph", sf::Style::Default, settings);
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
		for (int i = 0; i < dijskstra_ans.size(); ++i) {
			window.draw(nodeCirclesDijskstra[i]);
			for (AirportNodes* neighbor : nodeListDijskstra[i].neighbors()) {
				float x1 = nodeListDijskstra[i].x();
				float y1 = nodeListDijskstra[i].y();
				float x2 = neighbor->x();
				float y2 = neighbor->y();

				// Draw the line
				sf::RectangleShape line = Line(x1, y1, x2, y2);
				window.draw(line);

				// Calculate the midpoint between the two nodes
				float midX = (x1 + x2) / 2.0f;
				float midY = (y1 + y2) / 2.0f;

				sf::Text label;
				label.setString("Distance: " + ); // distance
				label.setCharacterSize(12);
				label.setFillColor(sf::Color::Black);
				label.setPosition(sf::Vector2f(midX, midY));

				window.draw(label);
			}
		window.display();
	}
  }
}

