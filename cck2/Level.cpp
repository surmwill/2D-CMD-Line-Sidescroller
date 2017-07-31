#include "Level.h"

using std::unique_ptr;
using std::vector;

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

vector <Enemy *> Level::enemiesAggrod(const Coordinate & playerPosition) {
	// vector of enemies that are aggrod who want to engage in combat with the player
	vector <Enemy *> enemiesAggrod;

	/* Go through the list of all enemies in the level, and see which
	ones are close enough to the player to be aggrod*/
	for (auto & enemy : enemies) {
		if (enemy->aggrod(playerPosition)) {
			enemiesAggrod.push_back(enemy.get());
		}
	}

	return enemiesAggrod;
}
