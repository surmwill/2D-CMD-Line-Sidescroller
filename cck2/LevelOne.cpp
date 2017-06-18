#include "LevelOne.h"
#include "LevelOneImpl.h"
#include "Map.h"

using std::make_shared;
using std::make_unique;

LevelOne::LevelOne() : 
	Level{ Coordinate{1,1} },
	levelImpl (make_unique <LevelOneImpl> ()) {
	// spawns the player on tile (1, 1)
	map->placePlayer(playerStart);

	/* reads in the level one's map to a vector, stores the 
	map's dimensions, and draws the map */
	map->readLevel("Levels\\LevelOne.txt");

	// ****************** fix this, player does not properly start at {2, 2} ***********************
	map->addressTileChange(Coordinate{ 2, 2 }, '*');
}


LevelOne::~LevelOne() {}

/* Returns our starting location for level one. This is 
passed onto the player class */
Coordinate LevelOne::getPlayerStart(void) {
	return Level::playerStart;
}

void LevelOne::findEnemies(void) {

}
