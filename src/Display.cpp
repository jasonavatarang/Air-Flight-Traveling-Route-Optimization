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
	RenderWindow window(VideoMode(450, 600), "Prompt");

	//loading in font
	Font font;
	if (!font.loadFromFile("data/font.ttf")) {
		std::cout << "Font not found!" << std::endl;
		return;
	}

	Text from_text, to_text, result_text, input_from_text, input_to_text, submit_label;

	// Set up "from" label
	from_text.setFont(font);
	from_text.setCharacterSize(20);
	from_text.setFillColor(Color::Black);
	from_text.setPosition(50.f, 60.f);
	from_text.setString("From Airport");

	//"from" textbox
	RectangleShape from_textbox(Vector2f(300.f, 30.f));
	from_textbox.setFillColor(Color::White);
	from_textbox.setOutlineColor(Color::Black);
	from_textbox.setOutlineThickness(2.f);
	from_textbox.setPosition(50.f, 100.f);

	input_from_text.setFont(font);
	input_from_text.setCharacterSize(20);
	input_from_text.setFillColor(Color::Black);
	input_from_text.setPosition(50.f, 100.f);

	//"to" textbox
	RectangleShape to_textbox(Vector2f(300.f, 30.f));
	to_textbox.setFillColor(Color::White);
	to_textbox.setOutlineColor(Color::Black);
	to_textbox.setOutlineThickness(2.f);
	to_textbox.setPosition(50.f, 200.f);

	input_to_text.setFont(font);
	input_to_text.setCharacterSize(20);
	input_to_text.setFillColor(Color::Black);
	input_to_text.setPosition(50.f, 200.f);

	// Set up "to" label
	to_text.setFont(font);
	to_text.setCharacterSize(20);
	to_text.setFillColor(Color::Black);
	to_text.setPosition(50.f, 160.f);
	to_text.setString("To Airport");

	RectangleShape button(Vector2f(170.f, 35.f));
	button.setFillColor(Color::Blue);
	button.setPosition(50.f, 250.f);

	// Set up "submit" label
	submit_label.setFont(font);
	submit_label.setString("Find Path :)");
	submit_label.setCharacterSize(24);
	submit_label.setFillColor(Color::White);
	submit_label.setPosition(50.f, 250.f);

	// Set up "result"
	result_text.setFont(font);
	result_text.setCharacterSize(20);
	result_text.setFillColor(Color::Black);
	result_text.setPosition(20.f, 300.f);

	path_output result;
	bool new_path = false;
	std::string from = "";
	std::string to = "";

	std::thread GraphWindow_thread([&] {GraphWindow(graph, from, to, new_path, result); });
	GraphWindow_thread.detach();
	bool from_textbox_selected = false;
	bool to_textbox_selected = false;

	//clicking on a textbox, button,  or closing the window
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonPressed:
			{
				// store mouse position
				Vector2i mousePos = Mouse::getPosition(window);

				// "from" textbox
				from_textbox_selected = from_textbox.getGlobalBounds().contains(mousePos.x, mousePos.y) ? true : false;

				// "to" text box
				to_textbox_selected = to_textbox.getGlobalBounds().contains(mousePos.x, mousePos.y) ? true : false;

				// submit button
				if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					// Update the from, to, and new_path variables
					from = input_from_text.getString();
					to = input_to_text.getString();
					std::cout << from << std::endl;
					std::cout << to << std::endl;
					new_path = true;
				}
				break;
			}
			case Event::TextEntered:
			{
				if (from_textbox_selected) {
					std::string temp = input_from_text.getString();
					if (event.text.unicode == '\b' && !temp.empty()) {
						temp.pop_back();
						input_from_text.setString(temp);
					}
					else if (event.text.unicode > 31 && event.text.unicode < 127) {
						input_from_text.setString(temp + event.text.unicode);
					}
				}
				else if (to_textbox_selected) {
					std::string temp = input_to_text.getString();
					if (event.text.unicode == '\b' && !temp.empty()) {
						temp.pop_back();
						input_to_text.setString(temp);
					}
					else if (event.text.unicode > 31 && event.text.unicode < 127) {
						input_to_text.setString(temp + event.text.unicode);
					}
				}
				break;
			}
			}
		}

		// Display results
		if (result.new_path) {
			result.new_path = false;
			if (result.displacement != 0) {
				std::string rslt;
				rslt += "Displacement on the Earth:\n" + std::to_string(result.displacement) + " km";
				rslt += "\n\nBFS (Green)\ntime: " + std::to_string(result.BFS_time) + " us" + "\ndistance: " + std::to_string(result.BFS_cost) + " km";
				rslt += "\n\nDijkstra (Yellow)\ntime: " + std::to_string(result.Dijkstra_time) + " us" + "\ndistance: " + std::to_string(result.Dijkstra_cost) + " km";
				rslt += "\n\nAstar (Red)\ntime: " + std::to_string(result.Astar_time) + " us" + "\ndistance: " + std::to_string(result.Astar_cost) + " km";
				result_text.setString(rslt);
			}
			else {
				result_text.setString("Cannot find a path!");
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
		window.draw(result_text); //text for result
		window.display();
	}
}


void GraphWindow(Graph& graph, std::string& from, std::string& to, bool& new_path, path_output& result)
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
			if (!(graph.search(from) && graph.search(to))) {
				result.displacement = 0;
				result.new_path = true;
				new_path = false;
				continue;
			}

			unsigned int cost, time;
			Color color;
			std::vector<std::string> path;
			std::unordered_set<std::string> stops;
			std::vector<std::pair<int, int>> bfs_pixel, dijk_pixel, astr_pixel; // pixel<x, y>

			// Get displacement
			result.displacement = graph.Displacement(from, to) / 1000;

			// Get new path from graph
			path = graph.BFS(from, to, cost, time);
			for (std::string& airport : path) {
				stops.insert(airport);
				bfs_pixel.push_back(coord2pixel(graph.getCoordinates(airport), window_size));
			}
			result.BFS_cost = cost / 1000;
			result.BFS_time = time;

			path = graph.Dijkstra(from, to, cost, time);
			for (std::string& airport : path) {
				stops.insert(airport);
				dijk_pixel.push_back(coord2pixel(graph.getCoordinates(airport), window_size));
			}
			result.Dijkstra_cost = cost / 1000;
			result.Dijkstra_time = time;

			path = graph.Astar(from, to, cost, time);
			for (std::string& airport : path) {
				stops.insert(airport);
				astr_pixel.push_back(coord2pixel(graph.getCoordinates(airport), window_size));
			}
			result.Astar_cost = cost / 1000;
			result.Astar_time = time;

			// Create objects representing airports
			for (auto iter = stops.begin(); iter != stops.end(); ++iter)
				airportDisplay(coord2pixel(graph.getCoordinates(*iter), window_size), airports);

			// Draw BFS paths
			color = Color::Green;
			for (int i = 1; i < bfs_pixel.size(); ++i)
				pathDisplay(bfs_pixel[i - 1], bfs_pixel[i], color, 6, paths);

			// Draw Dijkstra path
			color = Color::Yellow;
			for (int i = 1; i < dijk_pixel.size(); ++i)
				pathDisplay(dijk_pixel[i - 1], dijk_pixel[i], color, 4, paths);

			// Draw Astar path
			color = Color::Red;
			for (int i = 1; i < astr_pixel.size(); ++i)
				pathDisplay(astr_pixel[i - 1], astr_pixel[i], color, 2, paths);

			result.new_path = true;
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


void airportDisplay(std::pair<int, int> airport, std::vector<CircleShape>& airports)
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
	paths[index].setOrigin(0, thickness / 2.0f);
	paths[index].setPosition(from.first, from.second);
	paths[index].setRotation(-atan2(from.second - to.second, to.first - from.first) * 180 / M_PI);
}
