#pragma once
#include <Windows.h>
#include <vector>
#include "Coordinate.h"
#include <utility>

struct DisplayImpl {
	DisplayImpl() : hOut(GetStdHandle(STD_OUTPUT_HANDLE)) {
		prevDisplay.reserve(mapHeight);
		for (int i = 0; i < mapHeight; i++) {
			std::vector <char> line;
			line.reserve(consoleWidth);

			for (int j = 0; j < consoleWidth; j++) {
				line.insert(line.end(), '`');
			}
			prevDisplay.emplace_back(line);
		}
		
	};

	const HANDLE hOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD cursor{ 0, 0 }; //Where the next character is to be outputted on the screen

	const SHORT consoleWidth = 81; //chars across (81)
	const SHORT consoleHeight = 31; //number of lines (25)
	const SHORT mapHeight = 25; // Lines 26 - 31 are reserved for dialogue / menu

	/* since most of the map will be spaces, if we start with a screen
	full of spaces and only redraw the non spaces we eliminate some redrawing */
	std::vector <std::vector <char>> prevDisplay;
};
