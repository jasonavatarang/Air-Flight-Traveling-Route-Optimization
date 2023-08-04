#include <thread>
#include "SFML/Graphics.hpp"
#include "Graph.h"
#include "Display.h"

using namespace sf;

void PromptWindow(void* graph)
{
	unsigned int width = 800;
	unsigned int height = 600;
	RenderWindow window(VideoMode(width, height), "Prompt");

	//
	// Add prompts
	//
	// Add two input textbox and one button
	//

	bool new_path = false;
	std::string from, to;
	std::thread GraphWindow_thread([&] {GraphWindow(graph, from, to, new_path); });
	GraphWindow_thread.detach();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{

			//
			// Add mouse press event
			//
			// When mouse.clicked on button, 
			//

			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		window.clear(Color::White);
		window.display();
	}
}


void GraphWindow(void* graph, std::string& from, std::string& to, bool& new_path)
{
	unsigned int width = 400;
	unsigned int height = 600;
	RenderWindow window(VideoMode(width, height), "graph", Style::Titlebar);
	while (window.isOpen())
	{
		// Don't receive any events
		Event event;
		while (window.pollEvent(event)) {}

		if (new_path) {

			//
			//
			// Get the path from graph, which are airport names
			//
			//
			// Get coordinates using getCoordinates method
			//
			// 
			// Turn real coordinates into pixels on screen 
			//
			//
			// Create dot objects representing airports (also their names?)
			// 
			//
			// Draw lines between dots
			//
			// 
			// Use sfml::::draw method to display all widgets
			//
			//

		}

		window.clear(Color::White);
		window.display();
	}
}