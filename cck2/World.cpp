#include "World.h"
#include "LevelOne.h"
#include <Windows.h>
#include "WorldImpl.h"
#include "Display.h"
#include "Enemy.h"
#include "Combatent.h"
#include "DisplayedMap.h"
#include "CmdInterpreter.h"
#include "DisplayCommands.h"
#include <memory>

//delete these
#include "Coordinate.h"
#include "Map.h"
#include "Iostream.h"
#include "Debug.h"

using std::make_unique;
using std::move;

class Observer;

/* Main constructor */
World::World(CmdInterpreter * const cmd) : worldImpl(make_unique <WorldImpl> ()) {
	// Restricts the display's access to the cmdInterpreter's public functions 
	auto displayCmd = make_unique <DisplayCommands>(cmd); 

	worldImpl->display = make_unique <Display>(move(displayCmd));

	//Restricts the map's access to the display's public functions
	auto displayedMap = make_unique <DisplayedMap>(worldImpl->display.get());

	/* Create a new map object which has yet to load a level. The
	display is the map's observer */
	Observer * map = new Map(move(displayedMap));

	/* Every Level and Enemy subclass has access to the map object.
	Note that noDelete prevents deletion of map pointer through the
	shared_ptr reset method so we can still pass the map as one of the
	player's observers */
	auto noDelete = [](Observer*) {};
	Level::map.reset(dynamic_cast <Map *> (map), noDelete);
	Enemy::map.reset(map, noDelete); //map is passed as an observer here

	/* Start at level one */
	worldImpl->level = make_unique <LevelOne>();

	/* cast playerInCombat to player for clarity. Combat constructor should
	take 2 combatents. Statistics should have general stats like health while
	playerStats should have advanced social stats. Consider removing enemy stats
	if it's not useful. Figure out how to pass both player and an enemy to the 
	combat class by aggroing the enemy in the game. Pass through level? */

	// Spawn the player and pass the map as one of the player's observers
	worldImpl->player = make_unique <Player>(map, worldImpl->level->getPlayerStart());
	//worldImpl->player = dynamic_cast <Player *> (worldImpl->playerInCombat.get());
	worldImpl->playerInCombat = static_cast <Combatent *> (worldImpl->player.get());
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

void World::animateWorld(void) {
	// make enemies continually patrol the map
	worldImpl->level->moveEnemies();
}
