#pragma once
//***************************************************************************80

#include <string>
#include <vector>
#include "Coordinate.h"
#include <ostream>
#include "DisplayedMap.h"
#include <memory>

//to delete
#include <iostream>
#include "Debug.h"

using std::string;
using std::ifstream;
using std::pair;
using std::vector;

struct MapImpl final {
	MapImpl(std::unique_ptr <DisplayedMap> display) : display(move(display)) {};

	/* the Map's dimensional properties */
	int width, height; 

	/* The amount of tiles we can see ahead from our current position (10, 10) */
	const int visibleDistanceX = 40, visibleDistanceY = 12; 

	Coordinate playerOrigin{ 1,1 };
	vector <vector <char>> visibleArea;
	vector <vector <char>> map;

	const char playerTile = '+';
	const char wallTile = '#';

	std::unique_ptr <DisplayedMap> display;

	// what enemies are represented by on the map
	const vector <char> enemyTiles{ '@', '&', 'D' };
};
