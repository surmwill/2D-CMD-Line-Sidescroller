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

/* We require being passed the display which we call 
directly to redraw the screen */
Map::Map(Display * const display):
	mapImpl(make_unique<MapImpl>(display)) {
}

/* The spawn point of the player on the map */
void Map::placePlayer(const Coordinate playerStart) {
	mapImpl->playerOrigin = playerStart;
}

Map::~Map() {}

/* Reads a map design from a text file into a vector, as well as 
storing the map's width and height */
void Map::readLevel(const string & mapTxtFile) {
	Fstream fstream{ mapTxtFile };

	/* Fill out the dimensions of the map. The -1 is b/ we start
	counting at 0 */
	mapImpl->width = fstream.firstLineLength() - 1;
	mapImpl->height = fstream.numLines() - 1;

	/* Read the map into a vector */
	mapImpl->map.reserve(mapImpl->width);
	mapImpl->map = std::move(fstream.readRectContent());

	updateVisibleArea();
}

/* Updates where the player (and by extension the vision origin) is on the map. If
it is not a valid location the player is not moved. Note that newOrigin directly 
corresponds to the player's position in the PlayerImpl class and thus, by modifying
newOrigin we are also modfying PlayerImpl::position. Returns true if the player is
moved */
bool Map::validMove(const Coordinate & newOrigin) {
	/* We aren't allowed to leave the map's boundaries */
	if (newOrigin.x < 0 || newOrigin.x > mapImpl->width) return false;
	else if (newOrigin.y < 0 || newOrigin.y > mapImpl->height) return false;

	/* We aren't allowed to move through walls */
	if (mapImpl->map[newOrigin.y][newOrigin.x] == mapImpl->wallTile) return false;

	/* Otherwise we have a valid move */
	return true;
}

// updates the visible area based on the players position of playerOrigin
void Map::updateVisibleArea() {
	/* Calculate the section of the map vector we are to display */
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
				visibleLine.insert(visibleLine.end(), mapImpl->playerTile);
			// Otherwise, draw the map tile
			else visibleLine.insert(visibleLine.end(), mapImpl->map[i][j]);
		}

		mapImpl->visibleArea.emplace_back(visibleLine);
	}

	// draws the section of the map
	notifyVisibleArea();
}

/* notifies the display of a change in the map's visible area so
the display knows how to redraw the screen */
void Map::notifyVisibleArea(void) {
	mapImpl->display->drawMap(mapImpl->visibleArea);
}

/* Adjusts the visible area of
the map after a player movement */
bool Map::addressTileChange(
	//todo create vector of changes that newTiles get updated to that differ from the map
	const Coordinate & tileCoord,
	const char newDesign) {

	/* If the player's tile is being updated, the player's position must
	have moved. */
	if (newDesign == mapImpl->playerTile) {
		/* the map is always once step behind in movement with respect to the player. If
		we have a valid move (not leaving the map etc...) update where the player is on the map */
		if (validMove(tileCoord)) {
			mapImpl->playerOrigin.x = tileCoord.x;
			mapImpl->playerOrigin.y = tileCoord.y;
			updateVisibleArea();

			// We have succesfully changed a tile on the map
			return true;
		}
		else return false; // We have not succesfully changed a tile on the map
	}
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