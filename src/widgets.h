#pragma once

using namespace ImGui;
void sidebar()
{
	int width = 100;
	int height = 600;
	SetNextWindowPos(ImVec2(0, 0));
	SetNextWindowSize(ImVec2(400, 100));
	Begin("Search Bar");
	char departureQuery[64]{}; // Departure city search query buffer
	char arrivalQuery[64]{};   // Arrival city search query buffer

	InputText("Departure City", departureQuery, sizeof(departureQuery));
	InputText("Arrival City", arrivalQuery, sizeof(arrivalQuery));

	if (Button("Find Distance"))
	{
		// Handle search button click event
		// You can use departureQuery and arrivalQuery values to perform the search
	}

	End();
}