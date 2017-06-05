#include "World.h"
#include "LevelOne.h"
#include <Windows.h>
#include "WorldImpl.h"
#include "Display.h"

//delete these
#include "Coordinate.h"
#include "Map.h"
#include "Iostream.h"

using std::make_unique;

class Observer;

/* Main constructor */
World::World() : worldImpl(make_unique <WorldImpl> ()) {
	/* Create a new map object which has yet to load a level. The
	display is the map's observer */
	Observer * map = new Map(worldImpl->display.get());

	/* Every Level subclass has access to the map object. This is 
	used to cleanly swap levels. Note noDelete prevents deletion 
	of map pointer through the shared_ptr reset method so we can still pass
	the map as one of the player's observers */
	auto noDelete = [](Observer*) {};
	Level::map.reset(dynamic_cast <Map *> (map), noDelete);

	/* Start at level one */
	worldImpl->level = make_unique <LevelOne>();

	// Spawn the player and pass the map as one of the player's observers
	worldImpl->player = make_unique <Player>(map, worldImpl->level->getPlayerStart());
}


World::~World() {}

World & World::movePlayer(const int direction) {
	switch (direction) {
	case VK_LEFT:
		worldImpl->player->moveLeft();
		break;
	case VK_RIGHT:
		worldImpl->player->moveRight();
		break;
	case VK_UP:
		worldImpl->player->moveUp();
		break;
	case VK_DOWN:
		worldImpl->player->moveDown();
		break;
	}
	return *this;
}
