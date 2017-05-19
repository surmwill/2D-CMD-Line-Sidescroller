#pragma once
//***************************************************************************80

#include "Fstream.h"
#include <string>
#include <vector>
#include "Coordinate.h"
#include <ostream>
#include "Display.h"

//to delete
#include <iostream>

using std::string;
using std::ifstream;
using std::pair;
using std::vector;

struct MapImpl final {
	MapImpl(const string & mapTxtFile, Display * const display) :
		fstream(mapTxtFile),
		display(display),
		width(fstream.firstLineLength() - 1), // -1 b/c start counting from 0 instead of 1
		height(fstream.numLines() - 1) {
		map.reserve(width);
	};

	Fstream fstream;

	/* the Map's dimensional properties */
	const int width, height; 
	const int minXBoundary = 0;
	const int minYBoundary = 0;

	/* The amount of tiles we can see ahead from our current position (10, 10) */
	const int visibleDistanceX = 40, visibleDistanceY = 12; 

	Coordinate visionOrigin{ 0, 0 }; 
	vector <vector <char>> visibleArea;
	vector <vector <char>> map;

	Display * const display;
};
