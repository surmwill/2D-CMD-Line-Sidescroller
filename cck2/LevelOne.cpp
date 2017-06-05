#include "LevelOne.h"
#include <memory>
#include "Map.h"

using std::make_shared;

LevelOne::LevelOne() : Level{ Coordinate{1,1} } {
	// spawns the player on tile (1, 1)
	map->placePlayer(playerStart);

	/* reads in the level one's map to a vector, stores the 
	map's dimensions, and draws the map */
	map->readLevel("LevelOne\\LevelOne.txt");
}


LevelOne::~LevelOne() {}

/* Returns our starting location for level one. This is 
passed onto the player class */
Coordinate LevelOne::getPlayerStart(void) {
	return Level::playerStart;
}
