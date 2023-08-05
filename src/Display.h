#pragma once
#include "SFML/Graphics.hpp"

struct path_output {
	bool new_path = false;
	unsigned int displacement = 0;
	unsigned int BFS_time = 0;
	unsigned int BFS_cost = 0;
	unsigned int Dijkstra_time = 0;
	unsigned int Dijkstra_cost = 0;
	unsigned int Astar_time = 0;
	unsigned int Astar_cost = 0;
};

void PromptWindow(Graph& graph);
void GraphWindow(Graph& graph, std::string& from, std::string& to, bool& new_path, path_output& result);

std::pair<int, int> coord2pixel(std::pair<double, double> coordinates, std::pair<int, int>& window_size);
void airportDisplay(std::pair<int, int> airport, std::vector<sf::CircleShape>& airports);
void pathDisplay(std::pair<int, int>& from, std::pair<int, int>& to, sf::Color& color, int thickness, std::vector<sf::RectangleShape>& paths);