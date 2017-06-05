#include "LevelOne.h"
#include <memory>
#include "Map.h"

using std::make_shared;

LevelOne::LevelOne(Observer ** const map, Display * const display) :
	Level{ Coordinate{1,1} } {
	auto noDelete = [](Observer*) {};
	*map = new Map{ "LevelOne\\LevelOne.txt", display, Level::playerStart};

	/* ensures we don't delete and replace the map pointer
	so we can still pass the map as one of the player's observers */
	Level::map.reset(*map, noDelete);
}


LevelOne::~LevelOne()
{
}

/* Returns our starting location for level one. This is 
passed onto the player class */
Coordinate LevelOne::getPlayerStart(void) {
	return Level::playerStart;
}
