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

/* Intializes the player and level (level by extension,
intializes the map) */
World::World() : worldImpl(make_unique <WorldImpl> ()) {
	Observer * map = nullptr;

	/* We want the Map to call a specific Display function to redraw the 
	entire screen. Since we don't want to write a Observer function geared
	towards only 1 type of observer (the display) and not other observers (the map)
	we cast the display from an Observer to it's actual class, Display */
	worldImpl->level = make_unique <LevelOne>(
		&map, dynamic_cast <Display *> (worldImpl->display.get()));

	worldImpl->player = make_unique <Player>(map, worldImpl->level->getPlayerStart());
}


World::~World() {
}

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
