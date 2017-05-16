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

using std::make_unique;
using std::vector;
using std::move;
using std::ostream;
using std::string;

/* We require a txt file with desired map design to read */
Map::Map(const std::string & mapTxtFile):
	mapImpl(make_unique<MapImpl>(mapTxtFile)) {
	/* reads in the contents of the entire (rectangular) map */
	mapImpl->map = std::move(mapImpl->fstream.readRectContent());
	//cout << "THE ENTIRE MAP \n" << *this << endl;
}


Map::~Map() {}

// updates the visible area based on the players position of visionOrigin
void Map::updateVisibleArea(void) {
	int fromChar = mapImpl->visionOrigin.x - mapImpl->visibleDistanceX;
	int toChar = mapImpl->visionOrigin.x + mapImpl->visibleDistanceX;
	int startLine = mapImpl->visionOrigin.y - mapImpl->visibleDistanceY;
	int endLine = mapImpl->visionOrigin.y + mapImpl->visibleDistanceY;

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
			visibleLine.insert(visibleLine.end(), mapImpl->map[i][j]);
		}

		mapImpl->visibleArea.emplace_back(visibleLine);
	}

	printVisibleArea();
}

/* notifies the display of a change in the map's visible area for
the display to update */
void Map::notifyVisibleArea(void) {
	int x;
}

/* Adjusts the visible area of
the map after a player movement */
void Map::addressTileChange(
	const Coordinate & tile,
	const char newDesign) {

	mapImpl->visionOrigin.x = tile.x;
	mapImpl->visionOrigin.y = tile.y;

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