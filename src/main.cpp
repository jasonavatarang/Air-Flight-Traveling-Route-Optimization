//#include "gui.h"
#include "Graph.h"
#include "Data.h"
#include <iostream>
#include <utility>

int main() {

	// Still want GUI?
	//window();

	//int mode = 0;
	//cin >> mode;

	if (mode == 1){}
	//TEST 1
	cout << "Test Case 1: " << endl;
	Graph object;
	object.airportCoordinates["Orlando"] = std::make_pair(28.54, 81.37);
	object.airportCoordinates["NYC"] = std::make_pair(35.15, 90.05);
	object.airportCoordinates["Memphis"] = std::make_pair(28.5, 81.4);
	object.airportCoordinates["Cincinatti"] = std::make_pair(39.10, 84.51);
	object.airportCoordinates["Boston"] = std::make_pair(42.36, 71.06);
	object.airportCoordinates["Raleigh"] = std::make_pair(35.78, 78.63);
	object.airportCoordinates["DC"] = std::make_pair(38.90, 77.04);

	object.insert("Orlando", "Cincinatti", 757);
	object.insert("Cincinatti", "Raleigh", 396);
	object.insert("Cincinatti", "NYC", 585);
	object.insert("NYC", "DC", 214);
	object.insert("NYC", "Boston", 184);
	object.insert("Boston", "Memphis", 1140);

	vector <string> ans;
	vector <string> ans2;
	ans = object.findShortestPath_Dijkstra("Orlando", "Memphis");
	ans2 = object.findShortestPath_Astar("Orlando", "Memphis");

	//Total - 2666 miles (only path - orlando - cincinatti - nyc - boston - memphis)
	for (string str : ans) {
		cout << str << " ";
	}
	cout << endl;
	for (string str : ans2)
	{
		cout << str << " ";
	}
	cout << endl;

	//TEST 2
	cout << "Test Case 2: " << endl;
	Graph object2;
	object2.airportCoordinates["Orlando"] = std::make_pair(28.54, 81.37);
	object2.airportCoordinates["NYC"] = std::make_pair(35.15, 90.05);
	object2.airportCoordinates["Memphis"] = std::make_pair(28.5, 81.4);
	object2.airportCoordinates["Cincinatti"] = std::make_pair(39.10, 84.51);
	object2.airportCoordinates["Boston"] = std::make_pair(42.36, 71.06);
	object2.airportCoordinates["Raleigh"] = std::make_pair(35.78, 78.63);
	object2.airportCoordinates["DC"] = std::make_pair(38.90, 77.04);

	object2.insert("Orlando", "Cincinatti", 757);
	object2.insert("Cincinatti", "Raleigh", 396);
	object2.insert("Cincinatti", "NYC", 585);
	object2.insert("NYC", "DC", 214);
	object2.insert("NYC", "Boston", 184);
	object2.insert("Boston", "Memphis", 1140);
	//LINE BELOW CONNECTS A SHORTER PATH
	object2.insert("Raleigh", "Memphis", 632);

	vector<string> ans11;
	vector<string> ans22;
	ans11 = object2.findShortestPath_Dijkstra("Orlando", "Memphis");
	ans22 = object2.findShortestPath_Astar("Orlando", "Memphis");

	for (string str : ans11)
	{
		cout << str << " ";
	}
	cout << endl;
	for (string str : ans22)
	{
		cout << str << " ";
	}
	cout << endl;

	//shorter of two paths 1785 mi - orlando  - cincinatti - raleigh - memphis
	
	//Graph g;
		//g.insert("A", "B", 10);
		//g.insert("B", "C", 30);
		//g.insert("A", "C", 60);
		//g.insert("C", "D", 5);"

	//vector<string> ans;

	//// Should be: A C D
	//ans = g.findShortestPath_BFS("A", "D");
	//for (string str : ans) {
	//	std::cout << str << " ";
	//}
	//std::cout << std::endl;

	//// Should be: A B C D
	//ans = g.findShortestPath_Astar("A", "D");
	//for (string str : ans) {
	//	std::cout << str << " ";
	//}
	//std::cout << std::endl;

	//// Should be: A B C D
	//ans = g.findShortestPath_Dijkstra("A", "D");
	//for (string str : ans) {
	//	std::cout << str << " ";
	//}
	//std::cout << std::endl;
}