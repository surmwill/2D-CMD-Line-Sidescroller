#pragma once
#include "Enemy.h"
#include <memory>
#include <string>
#include "TalDoonCultist.h"
#include "Coordinate.h"
#include <map>
#include <functional>

class EnemyConstructor {
	/* Store how to construct each Enemy in a dictionary. By searching an enemy type
	we call a function pointer which returns the corresponding enemy's class */
	std::map < std::string, std::function<std::unique_ptr <Enemy> (const Coordinate &)>> enemyMap;

public:
	EnemyConstructor(void) {
		// note that compiler does strong type checking to ensure the return type of the lambda is an Enemy
		enemyMap["Tal'Doon Cultist"] = [](const Coordinate & origin) {return std::make_unique <TalDoonCultist>(origin); };
	}

	// search the map and call the corresponding lambda which returns a unique_ptr to the corresponding enemy
	std::unique_ptr <Enemy> construct(const std::string & enemyType, const Coordinate & origin) {
		return (enemyMap.find(enemyType)->second)(origin);
	}
};
