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

LevelOne::LevelOne() : 
	Level{ Coordinate{1,1} },
	levelImpl (make_unique <LevelOneImpl> ()) {
	// spawns the player on tile (1, 1)
	map->placePlayer(playerStart);

	/* reads in the level one's map to a vector, stores the 
	map's dimensions, and draws the map */
	map->readLevel("Levels\\LevelOne.txt");

	// ****************** fix this, player does not properly start at {2, 2} ***********************
	map->addressTileChange(Coordinate{ 2, 2 }, '*');

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
	vector <Enemy> en;

	while (getline(ifs, line)) {
		stringstream ss{ line };

		// Example format: "* x: 34 y: 35"
		ss >> tile; //read the tile '*'
		ss >> dummy; //read x: (unimportant so store in dummy)
		ss >> origin.x; //read x-coordinate '34'
		ss >> dummy; //read y: (unimportant so store in dummy)
		ss >> origin.y; //read y-coordinate '35'

		enemies.emplace_back(origin, tile);

		//construct the enemy
		//enemies.emplace_back(e);
	}
}
