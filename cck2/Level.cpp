#include "Level.h"
#include <algorithm>
#include "Debug.h"

using std::unique_ptr;
using std::vector;
using std::remove_if;
using std::find;

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

vector <Combatent *> Level::enemiesAggrod(const Coordinate & playerPosition) {
	// vector of enemies that are aggrod who want to engage in combat with the player
	vector <Combatent *> enemiesAggrod;

	/* Go through the list of all enemies in the level, and see which
	ones are close enough to the player to be aggrod*/
	for (auto & enemy : enemies) {
		if (enemy->aggrod(playerPosition)) {
			enemiesAggrod.push_back(static_cast <Combatent*> (enemy.get()));
		}
	}

	//cast to combatents
	return enemiesAggrod;
}

void Level::enemyCleanup(const vector <Enemy *> & deceased) {
	// remove all enemies from the level found in the vector of deceased enemies
	remove_if(
		enemies.begin(), 
		enemies.end(),
		[&deceased](const unique_ptr <Enemy> & enemy) {
		return find(deceased.begin(), deceased.end(), enemy.get()) != deceased.end();
	});

	//Debug::write(enemies.size());
}
