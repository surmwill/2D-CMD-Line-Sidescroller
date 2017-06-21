#pragma once
#include "Display.h"

/* The purpose of this class is to ensure the map class can
only call Display's drawMap function and not it's drawDialogue 
function */
class DisplayedMap
{
	Display * const display;

public:
	DisplayedMap(Display * const display) : display{ display } {};
	~DisplayedMap() = default;

	void drawMap(std::vector <std::vector <char>> & newTiles) {
		display->drawMap(newTiles);
	}
};

