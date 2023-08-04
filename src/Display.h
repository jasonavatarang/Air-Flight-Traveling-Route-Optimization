#pragma once

void PromptWindow(Graph& graph);
void GraphWindow(Graph& graph, std::string& from, std::string& to, bool& new_path);

std::pair<int, int> coord2pixel(std::pair<double, double> coordinates, std::pair<int, int>& window_size);
void airportDisplay(std::pair<int, int> airport, std::vector<sf::CircleShape>& airports);
void pathDisplay(std::pair<int, int>& from, std::pair<int, int>& to, sf::Color& color, int thickness, std::vector<sf::RectangleShape>& paths);