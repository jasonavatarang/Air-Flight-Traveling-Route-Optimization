#include <thread>
#include <unordered_set>
#include <iostream>
#include <corecrt_math_defines.h>

#include "SFML/Graphics.hpp"

#include "Graph.h"
#include "Display.h"


using namespace sf;


void PromptWindow(Graph& graph)
{
	int width = 800;
	int height = 600;
	RenderWindow window(VideoMode(width, height), "Prompt");

	Font font;
	if (!font.loadFromFile("data/font.ttf")) {
		std::cout << "Font not found!" << std::endl;
		return;
	}

	Text from_text, to_text;
	RectangleShape submit_button;

	// Set up "from" textbox
	from_text.setFont(font);
	from_text.setCharacterSize(20);
	from_text.setFillColor(sf::Color::Black);
	from_text.setPosition(50.f, 50.f);

	// Set up "to" textbox
	to_text.setFont(font);
	to_text.setCharacterSize(20);
	to_text.setFillColor(sf::Color::Black);
	to_text.setPosition(50.f, 100.f);

	// Set up "submit" button
	submit_button.setSize(Vector2f(100.f, 40.f));
	submit_button.setFillColor(sf::Color::Green);
	submit_button.setPosition(50.f, 150.f);


	bool new_path = true;
	std::string from = "Yaoqiang Airport";
	std::string to = "John F Kennedy International Airport";


	std::thread GraphWindow_thread([&] {GraphWindow(graph, from, to, new_path); });
	GraphWindow_thread.detach();


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			else if (event.type == Event::MouseButtonPressed)
			{
				// Check if the mouse clicked on the submit button
				Vector2i mousePos = Mouse::getPosition(window);
				if (submit_button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
				{
					// Update the from, to, and new_path variables
					from = from_text.getString();
					to = to_text.getString();
					new_path = true; // Set the flag to indicate that new input is available
				}
			}
		}

		window.clear(Color::White);
		// Draw GUI elements
		window.draw(from_text);
		window.draw(to_text);
		window.draw(submit_button);
		window.display();
	}
}


void GraphWindow(Graph& graph, std::string& from, std::string& to, bool& new_path)
{
	std::pair<int, int> window_size(1000, 800); // window_size<width, height>
	RenderWindow window(VideoMode(window_size.first, window_size.second), "graph", Style::Titlebar);

	// Widgets
	std::vector<CircleShape> airports;
	std::vector<RectangleShape> paths;

	while (window.isOpen())
	{
		// Don't receive any events
		Event event;
		while (window.pollEvent(event)) {}

		if (new_path) {
			unsigned int cost, time;
			Color color;
			std::vector<std::string> path;
			std::unordered_set<std::string> stops;
			std::vector<std::pair<int, int>> bfs_pixel, dijk_pixel, astr_pixel; // pixel<x, y>

			// Get new path from graph
			path = graph.BFS(from, to, cost, time);
			for (std::string& airport : path) {
				stops.insert(airport);
				bfs_pixel.push_back(coord2pixel(graph.getCoordinates(airport), window_size));
			}
			path = graph.Dijkstra(from, to, cost, time);
			for (std::string& airport : path) {
				stops.insert(airport);
				dijk_pixel.push_back(coord2pixel(graph.getCoordinates(airport), window_size));
			}
			path = graph.Astar(from, to, cost, time);
			for (std::string& airport : path) {
				stops.insert(airport);
				astr_pixel.push_back(coord2pixel(graph.getCoordinates(airport), window_size));
			}

			// Create objects representing airports (also their names?)
			for (auto iter = stops.begin(); iter != stops.end(); ++iter) {
				airportDisplay(coord2pixel(graph.getCoordinates(*iter), window_size), airports);
			}

			// Draw Dijkstra path
			color = Color::Red;
			for (int i = 1; i < dijk_pixel.size(); ++i)
				pathDisplay(dijk_pixel[i - 1], dijk_pixel[i], color, paths);

			// Draw Astar path
			color = Color::Blue;
			for (int i = 1; i < astr_pixel.size(); ++i)
				pathDisplay(astr_pixel[i - 1], astr_pixel[i], color, paths);

			new_path = false;
		}

		window.clear(Color::White);

		// Draw widgets
		for (CircleShape& airport : airports)
			window.draw(airport);
		for (RectangleShape& path : paths)
			window.draw(path);

		window.display();
	}
}


std::pair<int, int> coord2pixel(std::pair<double, double> coordinates, std::pair<int, int>& window_size)
{
	return std::pair<int, int>(round(coordinates.second / 360.0 * window_size.first + window_size.first / 2.0), round(-coordinates.first / 180.0 * window_size.second + window_size.second / 2.0));
}


void airportDisplay(std::pair<int, int> airport, std::vector<sf::CircleShape>& airports)
{
	int radius = 5;
	int index = airports.size();
	airports.emplace_back(radius);
	airports[index].setPosition(airport.first - radius, airport.second - radius);
	airports[index].setFillColor(Color::Black);
}


void pathDisplay(std::pair<int, int>& from, std::pair<int, int>& to, Color& color, std::vector<RectangleShape>& paths)
{
	int thickness = 2;
	int index = paths.size();
	paths.emplace_back(Vector2f(sqrt(pow(from.first - to.first, 2) + pow(from.second - to.second, 2)), thickness));
	paths[index].setFillColor(color);
	paths[index].setOrigin(Vector2f(0, thickness / 2));
	paths[index].setPosition(Vector2f(from.first, from.second));
	paths[index].setRotation(-atan2(from.second - to.second, to.first - from.first) * 180 / M_PI);
}
