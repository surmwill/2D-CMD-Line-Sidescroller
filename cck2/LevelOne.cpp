#include "LevelOne.h"
#include "LevelOneImpl.h"
#include "Map.h"
#include <fstream>
#include <sstream>

#include "Debug.h"

using std::make_shared;
using std::make_unique;
using std::ifstream;
using std::getline;
using std::string;
using std::stringstream;
using std::move;

LevelOne::LevelOne() : Level{ Coordinate{1,1} }, levelImpl (make_unique <LevelOneImpl> ()) {
	// spawns the player on tile (1, 1)
	map->placePlayer(playerStart);

	/* reads in the level one's map to a vector, stores the 
	map's dimensions, and draws the map */
	map->readLevel("Levels\\LevelOne.txt");

	// ****************** fix this, player does not properly start at {2, 2} ***********************
	map->addressTileChange(Coordinate{ 2, 2 }, '*');

	// The types of enemies we have in level one
	enemyLookup['*'] = "Tal'Doon Cultist";

	// Find where the enemies are on the map and construct them
	findEnemies();
}


LevelOne::~LevelOne() {}

/* Returns our starting location for level one. This is 
passed onto the player class */
Coordinate LevelOne::getPlayerStart(void) {
	return Level::playerStart;
}

void LevelOne::findEnemies(void) {
	ifstream ifs("EnemyInfo\\LevelOne.txt");
	string line;
	string dummy;
	char tile;
	Coordinate origin;

	while (getline(ifs, line)) {
		stringstream ss{ line };

		// Example format: "* x: 34 y: 35"
		ss >> tile; //read the tile '*'
		ss >> dummy; //read x: (unimportant so store in dummy)
		ss >> origin.x; //read x-coordinate '34'
		ss >> dummy; //read y: (unimportant so store in dummy)
		ss >> origin.y; //read y-coordinate '35'

		// Look up the enemy type based on level (multiple eneimies can be represented by '*', for example)
		const string enemyType = enemyLookup.find(tile)->second;

		// Construct the enemy, store in level
		auto enemy = move(enemyConstructor.construct(enemyType, Coordinate{ origin.x, origin.y }));
		enemies.push_back(std::move(enemy));
	}
}
