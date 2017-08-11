#include "Combat.h"
#include "Player.h"
#include "Enemy.h"
#include <algorithm>
#include "Debug.h"
#include "Error.h"

using std::vector;
using std::transform;
using std::back_inserter;
using std::unique_ptr;

/* Used to safely dynamic cast one class to another,
If the cast fails, an errow is thrown */
template <typename From, typename To> 
To * dynamic_caster(From * base) {
	To * derived = dynamic_cast <To *> (base);
	if (derived) return derived;
	else throw Error("could not dynamic cast");
}

Combat::Combat(
	vector <Combatent *> & friendlies,
	vector <Combatent *> & enemies) : friendlies{ friendlies }, enemies{ enemies } {
	//we assume that the majority of the time, the player will win the battle
	deadEnemies.reserve(enemies.size()); 
	nextStage();
}

Combat::Combat(
	Combatent * const player,
	vector <Combatent *> & enemies) : player{ player }, enemies{ enemies } {
	//we assume that the majority of the time, the player will win the battle
	deadEnemies.reserve(enemies.size());
	nextStage();
}


Combat::~Combat(){
}

void Combat::nextStage(void) {
	bool victorious = true;

	//check leadership stat to see who goes first
	// for now... the player goes first
	player->takeTurn();
	if (player->isDead()) { 
		// game over
	}

	//friendlies take turn

	//then the enemies
	for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt) {
		Combatent * enemy = *enemyIt;

		if (enemy->isDead()) continue; // dead enemies can't do anything (except wait for a possible ressurection)
		else enemy->takeTurn();

		// while there is still an enemy remaining we haven't achieved victory
		victorious = false;
	}

	Debug::write("victorius");

	// or if the player succesfully flees the fight (add fn later)
	if (victorious) return; 
}

std::vector <Enemy *> Combat::reportDeadEnemies(void) {
	// Cast our enemies from Combatents to Enemies
	vector <Enemy *> downcastEnemies;
	downcastEnemies.reserve(enemies.size());

	// Determine which enemies are dead and need to be cleared from the game
	for (auto & enemy : enemies) {
		if (enemy->isDead()) {
			try {
				downcastEnemies.push_back(dynamic_caster <Combatent, Enemy>(enemy));
			}
			catch (Error & error) {
				Debug::write(error.getMessage());
				throw;
			}
		}
	}

	Debug::write(downcastEnemies.size());

	return downcastEnemies;
}