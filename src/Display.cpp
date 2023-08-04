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

	//loading in font
	Font font;
	if (!font.loadFromFile("data/font.ttf")) {
		std::cout << "Font not found!" << std::endl;
		return;
	}

	Text from_text, to_text;

	// Set up "from" label
	from_text.setFont(font);
	from_text.setCharacterSize(20);
	from_text.setFillColor(sf::Color::Black);
	from_text.setPosition(50.f, 50.f);
	from_text.setString("From Airport");

	//"from" textbox
	sf::RectangleShape from_textbox(sf::Vector2f(200.f, 30.f));
	from_textbox.setFillColor(sf::Color::White);
	from_textbox.setOutlineColor(sf::Color::Black);
	from_textbox.setOutlineThickness(2.f);
	from_textbox.setPosition(50.f, 100.f);
	Text input_from_text;
	input_from_text.setFont(font);
	input_from_text.setCharacterSize(20);
	input_from_text.setFillColor(sf::Color::Black);
	input_from_text.setPosition(50.f, 100.f);


	//"to" textbox
	sf::RectangleShape to_textbox(sf::Vector2f(200.f, 30.f));
	to_textbox.setFillColor(sf::Color::White);
	to_textbox.setOutlineColor(sf::Color::Black);
	to_textbox.setOutlineThickness(2.f);
	to_textbox.setPosition(50.f, 200.f);

	Text input_to_text;
	input_to_text.setFont(font);
	input_to_text.setCharacterSize(20);
	input_to_text.setFillColor(sf::Color::Black);
	input_to_text.setPosition(50.f, 200.f);

	RectangleShape button(sf::Vector2f(200.f, 50.f));
	button.setFillColor(sf::Color::Blue);
	button.setPosition(50.f, 250.f);	// Set up "submit" button

	// Set up "submit" label
	Text submit_label;
	submit_label.setFont(font);
	submit_label.setString("Find Path:)");
	submit_label.setCharacterSize(24);
	submit_label.setFillColor(sf::Color::White);
	submit_label.setPosition(50.f, 250.f);

	bool new_path = false;
	//std::string from = "Yaoqiang Airport";
	//std::string to = "John F Kennedy International Airport";
	std::string from = "";
	std::string to = "";

	std::thread GraphWindow_thread([&] {GraphWindow(graph, from, to, new_path); });
	GraphWindow_thread.detach();
	bool from_textbox_selected = false;
	bool to_textbox_selected = false;

	//clicking on a textbox, button,  or closing the window
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
				// store mouse position
				Vector2i mousePos = Mouse::getPosition(window);

				// "from" textbox
				if (from_textbox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
				{
					from_textbox_selected = true;
				}
				else
				{
					from_textbox_selected = false;
				}

				// "to" text box
				if (to_textbox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
				{
					to_textbox_selected = true;
				}
				else
				{
					to_textbox_selected = false;
				}


				// submit button
				if (button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
				{
					// Update the from, to, and new_path variables
					std::cout << from << std::endl;
					std::cout << to << std::endl;
					new_path = true;
				}
			}
			else if (event.type == Event::TextEntered) {
				if (from_textbox_selected) {
					if (event.text.unicode < 128) {
						if (event.text.unicode == '\b' && !input_from_text.getString().isEmpty()) {
							std::string temp = input_from_text.getString();
							temp.pop_back();
							input_from_text.setString(temp);
						}
						else {
							input_from_text.setString(input_from_text.getString() + static_cast<char>(event.text.unicode));

						}
						from = input_from_text.getString();
					}
				}
				if (to_textbox_selected) {
					if (event.text.unicode < 128) {
						if (event.text.unicode == '\b' && !input_to_text.getString().isEmpty()) {
							std::string temp = input_to_text.getString();
							temp.pop_back();
							input_to_text.setString(temp);
						}
						else {
							input_to_text.setString(input_to_text.getString() + static_cast<char>(event.text.unicode));

						}
						to = input_to_text.getString();
					}
				}
			}
		}

		window.clear(Color::White);
		// Draw GUI elements
		window.draw(from_text); // label
		window.draw(from_textbox); // box
		window.draw(input_from_text); // input
		window.draw(to_text); //label
		window.draw(to_textbox); //box
		window.draw(input_to_text); //input
		window.draw(button); //button
		window.draw(submit_label); //text for button
		window.display();
	}
}

void GraphWindow(Graph& graph, std::string& from, std::string& to, bool& new_path)
{
	std::pair<int, int> window_size(1600, 800); // window_size<width, height>
	RenderWindow window(VideoMode(window_size.first, window_size.second), "graph", Style::Titlebar);

	// Background Earth
	Texture bgImage;
	Sprite background;
	if (bgImage.loadFromFile("data/Earth.png")) {
		background.setTexture(bgImage);
		background.setScale(window_size.first / background.getLocalBounds().width, window_size.second / background.getLocalBounds().height);
	}

	// Widgets
	std::vector<CircleShape> airports;
	std::vector<RectangleShape> paths;

	while (window.isOpen())
	{
		// Don't receive any events
		Event event;
		while (window.pollEvent(event)) {}

		if (new_path) {
			// Clear the vectors
			airports.clear();
			paths.clear();

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
			std::cout << cost << std::endl;
			path = graph.Dijkstra(from, to, cost, time);
			for (std::string& airport : path) {
				stops.insert(airport);
				dijk_pixel.push_back(coord2pixel(graph.getCoordinates(airport), window_size));
			}
			std::cout << cost << std::endl;
			path = graph.Astar(from, to, cost, time);
			for (std::string& airport : path) {
				stops.insert(airport);
				astr_pixel.push_back(coord2pixel(graph.getCoordinates(airport), window_size));
			}
			std::cout << cost << std::endl;

			// Create objects representing airports (also their names?)
			for (auto iter = stops.begin(); iter != stops.end(); ++iter) {
				airportDisplay(coord2pixel(graph.getCoordinates(*iter), window_size), airports);
			}

			// Draw BFS path
			color = Color::Green;
			for (int i = 1; i < bfs_pixel.size(); ++i)
				pathDisplay(bfs_pixel[i - 1], bfs_pixel[i], color, 6, paths);

			// Draw Dijkstra path
			color = Color::Red;
			for (int i = 1; i < dijk_pixel.size(); ++i)
				pathDisplay(dijk_pixel[i - 1], dijk_pixel[i], color, 4, paths);

			// Draw Astar path
			color = Color::Blue;
			for (int i = 1; i < astr_pixel.size(); ++i)
				pathDisplay(astr_pixel[i - 1], astr_pixel[i], color, 2, paths);

			new_path = false;
		}

		window.clear();
		window.draw(background);

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


void pathDisplay(std::pair<int, int>& from, std::pair<int, int>& to, Color& color, int thickness, std::vector<RectangleShape>& paths)
{
	int index = paths.size();
	paths.emplace_back(Vector2f(sqrt(pow(from.first - to.first, 2) + pow(from.second - to.second, 2)), thickness));
	paths[index].setFillColor(color);
	paths[index].setOrigin(0, thickness / 2);
	paths[index].setPosition(from.first, from.second);
	paths[index].setRotation(-atan2(from.second - to.second, to.first - from.first) * 180 / M_PI);
}
