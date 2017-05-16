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
	worldImpl->level = make_unique <LevelOne>(&map, (worldImpl->display).get());
	worldImpl->player = make_unique <Player>(map);
	//worldImpl->display.refresh();
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
