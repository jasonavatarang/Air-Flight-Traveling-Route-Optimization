#include <thread>
#include <unordered_set>
#include <iostream>

#include "SFML/Graphics.hpp"

#include "Graph.h"
#include <SFML/Window.hpp>
#include "Display.h"

using namespace sf;

void SetupGUI(RenderWindow& window, Font& font, Text& from_text, Text& to_text, RectangleShape& submit_button)
{
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
}

void PromptWindow(Graph& graph)
{
	unsigned int width = 800;
	unsigned int height = 600;
	RenderWindow window(VideoMode(width, height), "Prompt");

	Font font;
	if (!font.loadFromFile("font.ttf")) {
		// Handle font loading failure
		return;
	}

	Text from_text, to_text;
	RectangleShape submit_button;

	SetupGUI(window, font, from_text, to_text, submit_button);


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
	std::pair<unsigned int, unsigned int> window_size(600, 800); // window_size<width, height>
	RenderWindow window(VideoMode(window_size.first, window_size.second), "graph", Style::Titlebar);
	while (window.isOpen())
	{
		// Don't receive any events
		Event event;
		while (window.pollEvent(event)) {}

		if (new_path) {
			unsigned int cost, time;
			std::vector<std::string> path;
			std::unordered_set<std::pair<unsigned int, unsigned int>> stops;
			std::vector<std::pair<unsigned int, unsigned int>> dijk_pixel, astr_pixel;

			// Get new path from graph
			path = graph.Dijkstra(from, to, cost, time);
			for (std::string& airport : path) {
				stops.insert(graph.getCoordinates(airport));
				dijk_pixel.push_back(coord2pixel(graph.getCoordinates(airport), window_size));
			}
			path = graph.Astar(from, to, cost, time);
			for (std::string& airport : path) {
				stops.insert(graph.getCoordinates(airport));
				astr_pixel.push_back(coord2pixel(graph.getCoordinates(airport), window_size));
			}

			// Create objects representing airports (also their names?)
			for (auto& stop : stops) {
				airportCreate(stop);
			}

			// Draw lines between dots
			// void pathCreate(pair<unsigned int, unsigned int>& from, pair<unsigned int, unsigned int>& to);
			//
			// 
			// Use sfml::::draw method to display all widgets
			//
			//
			new_path = false;
		}

		window.clear(Color::White);
		window.display();
	}
}

std::pair<unsigned int, unsigned int> coord2pixel(std::pair<double, double> coordinates, std::pair<unsigned int, unsigned int>& window_size)
{
	return std::pair<unsigned int, unsigned int>(coordinates.second / 360.0 * window_size.first + window_size.first / 2.0, -coordinates.first / 180.0 * window_size.second + window_size.second / 2.0);
}

void airportCreate(std::pair<unsigned int, unsigned int> airport)
{
}

void pathCreate(std::pair<unsigned int, unsigned int>& from, std::pair<unsigned int, unsigned int>& to)
{
}
