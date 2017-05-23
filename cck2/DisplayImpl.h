#pragma once
#include <Windows.h>
#include <vector>

//displayImpl->hOut(GetStdHandle(STD_OUTPUT_HANDLE))

struct DisplayImpl {
	DisplayImpl() : hOut(GetStdHandle(STD_OUTPUT_HANDLE)) {
		prevDisplay.reserve(consoleHeight);
		for (int i = 0; i < consoleHeight; i++) {
			std::vector <char> line;
			line.reserve(consoleWidth);

			for (int j = 0; j < consoleWidth; j++) {
				line.insert(line.end(), '+');
			}
			prevDisplay.emplace_back(line);
		}
		
	};

	const HANDLE hOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	const SHORT consoleWidth = 81; //chars across (81)
	const SHORT consoleHeight = 25; //number of lines (25)

	/* since most of the map will be spaces, if we start with a screen
	full of spaces and only redraw the non spaces we eliminate some redrawing */
	std::vector <std::vector <char>> prevDisplay;
};
