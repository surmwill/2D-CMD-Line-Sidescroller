#include "Combat.h"
#include "Player.h"
#include "Enemy.h"

//next steps, make the vector of enemy combatents unqiue_ptrs instead of raw pointers so we can delete them from the map when they die

using std::vector;

Combat::Combat(
	vector <Combatent *> & friendlies,
	vector <Combatent *> & enemies) : friendlies{ friendlies }, enemies{ enemies } {
	nextStage();
}

Combat::Combat(
	Combatent * const player,
	vector <Combatent *> & enemies) : player{ player }, enemies{ enemies } {
}


Combat::~Combat(){
}

void Combat::nextStage(void) {
	//check leadership stat to see who goes first
	// for now... the player goes first
	player->takeTurn();
	if (player->isDead()) { 
		// game over
	}

	//then the enemies
	for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt) {
		auto enemy = *enemyIt;

		enemy->takeTurn();
		if (enemy->isDead()) {
			//clear the enemy from the map
			enemies.erase(enemyIt); //remove the enemy from the list of enemies we need to fight
		}
	}
}

