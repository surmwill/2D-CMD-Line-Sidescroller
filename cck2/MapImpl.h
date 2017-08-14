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
	MapImpl(std::unique_ptr <DisplayedMap> display, const int mapWidth, const int mapHeight) :
		display(move(display)),
		visibleDistanceX(mapWidth / 2), // we can see half of the mapWidth either way
		visibleDistanceY(mapHeight / 2) {}; // we can see half of the mapHeight either way
		// note this means if we are in the center of the map, the entire screen will be filled

	/* the Map's dimensional properties */
	int width, height; 

	/* The amount of tiles we can see ahead from our current position (10, 10) */
	//const int visibleDistanceX = 40, visibleDistanceY = 11; //40, 12 
	const int visibleDistanceX;
	const int visibleDistanceY;

	Coordinate playerOrigin{ 1,1 };
	vector <vector <char>> visibleArea;
	vector <vector <char>> map;

	const char playerTile = '+';
	const char wallTile = '#';

	std::unique_ptr <DisplayedMap> display;

	// what enemies are represented by on the map
	const vector <char> enemyTiles{ '@', '&', 'D' };
};
