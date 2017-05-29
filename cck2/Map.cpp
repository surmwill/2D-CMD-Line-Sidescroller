//***************************************************************************80
#include "Map.h"
#include "MapImpl.h"
#include "Coordinate.h"
#include <vector>
#include <algorithm>
#include "Iostream.h"
#include "Fstream.h"
#include <string>
#include <utility>
#include "Coordinate.h"
#include "Display.h"

//to delete
//#include "Debug.h"

using std::make_unique;
using std::vector;
using std::move;
using std::ostream;
using std::string;

/* We require a txt file with desired map design to read and the display
which we call directly to redraw the screen */
Map::Map(const std::string & mapTxtFile, Display * const display):
	mapImpl(make_unique<MapImpl>(mapTxtFile, display)) {
	/* reads in the contents of the entire (rectangular) map */
	mapImpl->map = std::move(mapImpl->fstream.readRectContent());

	updateVisibleArea();
}


Map::~Map() {}

// updates the visible area based on the players position of playerOrigin
void Map::updateVisibleArea(void) {
	int fromChar = mapImpl->playerOrigin.x - mapImpl->visibleDistanceX;
	int toChar = mapImpl->playerOrigin.x + mapImpl->visibleDistanceX;
	int startLine = mapImpl->playerOrigin.y - mapImpl->visibleDistanceY;
	int endLine = mapImpl->playerOrigin.y + mapImpl->visibleDistanceY;

	if (fromChar < 0) fromChar = 0;
	if (toChar > mapImpl->width) toChar = mapImpl->width;
	if (startLine < 0) startLine = 0;
	if (endLine > mapImpl->height) endLine = mapImpl->height;
	
	/* add 1 because we can see visibleDistance tiles either direction
	AND we can see the tile we are currently on */
	int charsToRead = toChar - fromChar + 1;
	int linesToRead = endLine - startLine + 1;

	//cout << fromChar << ' ' << charsToRead << ' ' << startLine << ' ' << linesToRead << ' ' << endl;

	/* Reads linesToRead lines from the map starting at startLine. For each line
	we read charsToRead chars originating from fromChar. The section of the map read 
	is defined as the visibleArea the player can see*/
	mapImpl->visibleArea.clear();
	mapImpl->visibleArea.reserve(linesToRead);

	for (int i = startLine; i < (startLine + linesToRead); i++) {
		vector <char> visibleLine;
		visibleLine.reserve(charsToRead);

		for (int j = fromChar; j < (fromChar + charsToRead); j++) {
			// If we are at the tile the player is at, don't draw the map tile, instead draw the player tile
			if (i == mapImpl->playerOrigin.y && j == mapImpl->playerOrigin.x)
				visibleLine.insert(visibleLine.end(), '+');
			// Otherwise, draw the map tile
			else visibleLine.insert(visibleLine.end(), mapImpl->map[i][j]);
		}

		mapImpl->visibleArea.emplace_back(visibleLine);
	}

	notifyVisibleArea();
}

/* notifies the display of a change in the map's visible area so
the display knows how to redraw the screen */
void Map::notifyVisibleArea(void) {
	mapImpl->display->drawMap(mapImpl->visibleArea);
}

/* Adjusts the visible area of
the map after a player movement */
void Map::addressTileChange(
	//todo create vector of changes that newTiles get updated to that differ from the map
	const Coordinate & tile,
	const char newDesign) {
	const char playerTile = '+';

	/* If the player's tile is being updated, the player's position must
	have moved. */
	if (newDesign == playerTile) {
		mapImpl->playerOrigin.x = tile.x;
		mapImpl->playerOrigin.y = tile.y;

		/* We aren't allowed to leave the map's boundaries */
		if (mapImpl->playerOrigin.x < 0) mapImpl->playerOrigin.x = 0;
		else if (mapImpl->playerOrigin.x > mapImpl->width) 
			mapImpl->playerOrigin.x = mapImpl->width;

		if (mapImpl->playerOrigin.y < 0) mapImpl->playerOrigin.y = 0;
		else if (mapImpl->playerOrigin.y > mapImpl->height) 
			mapImpl->playerOrigin.y = mapImpl->height;
	}

	updateVisibleArea();
}

//prints out the entire map
ostream & operator<<(ostream & out, const Map & map) {
	for (auto row : map.mapImpl->map) {
		for (auto col : row) {
			out << col;
		}
		out << '\n';
	}

	return out;
}

//prints out the visible area (for testing)
void Map::printVisibleArea(void) const {
	for (auto row : mapImpl->visibleArea) {
		for (auto col : row) {
			cout << col;
		}
		cout << '\n';
	}

	cout << '\n';
}