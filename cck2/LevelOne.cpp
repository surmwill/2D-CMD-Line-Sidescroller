#include "LevelOne.h"
#include <memory>
#include "Map.h"

using std::make_shared;

LevelOne::LevelOne(Observer ** const map) {
	auto noDelete = [](Observer*) {};
	*map = new Map{ "LevelOne\\LevelOne.txt" };

	/* ensures we don't delete and replace the map pointer
	so we can still pass the map as one of the player's observers */
	Level::map.reset(*map, noDelete);
}


LevelOne::~LevelOne()
{
}
