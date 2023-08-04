#include <thread>
#include <unordered_set>
#include <iostream>

#include "SFML/Graphics.hpp"

#include "Graph.h"
#include "Display.h"

using namespace sf;


void PromptWindow(Graph& graph)
{
	unsigned int width = 800;
	unsigned int height = 600;
	RenderWindow window(VideoMode(width, height), "Prompt");

	Font font;
	if (!font.loadFromFile("data/font.ttf")) {
		std::cout << "Font not found!" << std::endl;
		return;
	}

	Text from_text, to_text;

	// Set up "from" lable
	from_text.setFont(font);
	from_text.setCharacterSize(20);
	from_text.setFillColor(sf::Color::Black);
	from_text.setPosition(50.f, 50.f);
	from_text.setString("From Airport");
	
	// from textbox
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

	// Set up "to" label
	to_text.setFont(font);
	to_text.setCharacterSize(20);
	to_text.setFillColor(sf::Color::Black);
	to_text.setPosition(50.f, 150.f);
	to_text.setString("To Airport");

	// to textbox
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
	button.setPosition(50.f,250.f);

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

				// from textbox
				if (from_textbox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
				{
					from_textbox_selected = true;
					//std::cout << "From Textbox selected!" << std::endl;
				}
				else
				{
					from_textbox_selected = false;
				}

				// to text box
				if (to_textbox.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
				{
					to_textbox_selected = true;
					//std::cout << "To Textbox selected!" << std::endl;
				}
				else
				{
					to_textbox_selected = false;
				}


				// submit
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
						//std::cout << from << std::endl;
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
						//std::cout << to << std::endl;
					}
				}
			}
		}

		window.clear(Color::White);
		// Draw GUI elements
		window.draw(from_text); // label
		window.draw(from_textbox); // box
		window.draw(input_from_text); // input
		window.draw(to_text);
		window.draw(to_textbox);
		window.draw(input_to_text);
		window.draw(button);
		window.draw(submit_label);
		window.display();
	}
}



void GraphWindow(Graph& graph, std::string& from, std::string& to, bool& new_path)
{
	std::pair<unsigned int, unsigned int> window_size(600, 800); // window_size<width, height>
	RenderWindow window(VideoMode(window_size.first, window_size.second), "graph", Style::Titlebar);

	// Widgets
	std::vector<CircleShape> airports;

	while (window.isOpen())
	{
		// Don't receive any events
		Event event;
		while (window.pollEvent(event)) {}

		if (new_path) {
			unsigned int cost, time;
			std::vector<std::string> path;
			std::unordered_set<std::string> stops;
			std::vector<std::pair<unsigned int, unsigned int>> dijk_pixel, astr_pixel;

			// Get new path from graph
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
	return std::pair<unsigned int, unsigned int>(round(coordinates.second / 360.0 * window_size.first + window_size.first / 2.0), round(-coordinates.first / 180.0 * window_size.second + window_size.second / 2.0));
}

void airportDisplay(std::pair<unsigned int, unsigned int> airport, std::vector<sf::CircleShape>& airports)
{
	//std::cout<<airport.first<<" "<<airport.
	//sf::CircleShape shape(50);

	//// set the shape color to green
	//shape.setFillColor(sf::Color(100, 250, 50));

}

void pathCreate(std::pair<unsigned int, unsigned int>& from, std::pair<unsigned int, unsigned int>& to)
{
}
