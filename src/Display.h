#pragma once

void PromptWindow(Graph& graph);
void GraphWindow(Graph& graph, std::string& from, std::string& to, bool& new_path);

std::pair<unsigned int, unsigned int> coord2pixel(std::pair<double, double> coordinates, std::pair<unsigned int, unsigned int>& window_size);
void airportCreate(std::pair<unsigned int, unsigned int> airport);
void pathCreate(std::pair<unsigned int, unsigned int>& from, std::pair<unsigned int, unsigned int>& to);