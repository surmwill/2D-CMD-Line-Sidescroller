#pragma once
#include <Windows.h>
#include <vector>
#include "Coordinate.h"
#include <utility>
#include "DisplayCommands.h"

struct DisplayImpl {
	DisplayImpl(std::unique_ptr <DisplayCommands> cmd) : hOut(GetStdHandle(STD_OUTPUT_HANDLE)), cmd{ std::move(cmd) } {
		prevDisplay.reserve(mapHeight); // Intializes the previous display dimenion's t that of our map
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

	const SHORT consoleHeight = 33; // 33 Lines total in the console: (0 - 32)

	// note the mapHeight and mapWidth must be odd to
	const SHORT mapHeight = 23; // 23 Lines: (0 - 22) are reserved for displaying the map and everything on it 
	const SHORT mapWidth = consoleWidth;

	const SHORT uiStarts = 23; // 4 Lines: (23 - 26) are reserved for diaplying the u.i 
	const SHORT dialogueStarts = 27; // 6 Lines (27 - 32) are reserved for printing dialogue 

	int currentDialogueLine = dialogueStarts; // The next avalible empty line for drawing dialogue
	const int dialogueLines = consoleHeight - dialogueStarts; //The number of lines availible for drawing dialogue (6)

	//The maximum length of a dialogue string that can be displayed, unsigned b/c I don't like warnings
	const unsigned int maxDialogueLength = dialogueLines * consoleWidth; 

	LPCWSTR title = L"CCK2"; //title of the game - to be displayed on the console window

	/* a character which should never show up on the map. The buffer is always 1 character behind
	where we are in the for loop. This is the buffer's initial character that it's fed that it knows not
	to print */
	const char tokenTile = '\t';

	/* since most of the map will be spaces, if we start with a screen
	full of spaces and only redraw the non spaces we eliminate some redrawing */
	std::vector <std::vector <char>> prevDisplay;

	/* Used for when we need player input to continue. An example would be waiting for
	the spacebar to be pressed before clearing read dialogue */
	std::unique_ptr <DisplayCommands> cmd;
};
