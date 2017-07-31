#include "Level.h"

using std::unique_ptr;

// initalized to something of significance in World's constructor
unique_ptr <Map> Level::map = nullptr;

/* Sets the player's spawn location in the level */
Level::Level(const Coordinate playerStart) :
	playerStart(playerStart) {
}

void Level::moveEnemies(void) {
	for (auto & enemy : enemies) {
		enemy->patrol();
	}
}
