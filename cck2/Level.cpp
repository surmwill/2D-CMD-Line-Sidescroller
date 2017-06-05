#include "Level.h"

using std::shared_ptr;

// initalized to something of significance in World's constructor
shared_ptr <Map> Level::map = nullptr;

/* Sets the player's spawn location in the level */
Level::Level(const Coordinate playerStart) :
	playerStart(playerStart) {
}
