#pragma once
#include "Enemy.h"
#include <memory>
#include <string>
#include "TalDoonCultist.h"
#include "Coordinate.h"

//make suffix trie with each enemy name, the last node will contain a function with returns the specific enemy object
class EnemyConstructor {

public:
	std::unique_ptr <Enemy> makeEnemy(const std::string & enemyType, const Coordinate & origin, const char tile) {
		if (enemyType == "Tal'Doon Cultist") return std::make_unique <TalDoonCultist>(origin, tile);
	}
};
