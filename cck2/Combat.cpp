#include "Combat.h"
#include "Player.h"
#include "Enemy.h"
#include <algorithm>
#include "Debug.h"
#include "Error.h"

//next steps, make the vector of enemy combatents unqiue_ptrs instead of raw pointers so we can delete them from the map when they die

using std::vector;
using std::transform;
using std::back_inserter;

/* A functor used to safely dynamic cast one class to another,
If the cast fails, an errow is thrown */
template <typename From, typename To> struct dynamic_caster {
	To * operator()(From * base) {
		To * derived = dynamic_cast <To *> (base);
		if (derived) return derived;
		else throw Error("could not dynamic cast");
	}
};

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

	//friendlies take turn

	//then the enemies
	for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt) {
		Combatent * enemy = *enemyIt;

		enemy->takeTurn();
		if (enemy->isDead()) {
			enemies.erase(enemyIt); //remove the enemy from the list of enemies we need to fight
			deadEnemies.push_back(dynamic_cast <Enemy *> (enemy)); //add the enemy to the list of enemies we are to delete from the level
		}
	}
}

std::vector <Enemy *> Combat::reportDeadEnemies(void) {
	// Cast our enemies from Combatents to Enemies
	vector <Enemy *> downcastEnemies;
	downcastEnemies.reserve(enemies.size());

	/* Fill our new downcasted Enemy array */
	try {
		transform(
			enemies.begin(),
			enemies.end(),
			back_inserter(downcastEnemies),
			dynamic_caster <Combatent, Enemy>());
	} // If a dynamic cast fails, catch the error and return nothing
	catch (Error & badCast) {
		Debug::write(badCast.getMessage());
		return vector <Enemy *> {};
	}

	return downcastEnemies;
}