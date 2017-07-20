#pragma once
#include "Enemy.h"
#include <memory>
#include <string>
#include "TalDoonCultist.h"
#include "Coordinate.h"
#include <map>

//ToDo make Enemy have no paramters to construct, when we search for an enemy in the map we return the enemy, then call
//a seperate enemy function as a secondary costructor to set the origin, tile, and aggro range/threat
//we need to do this b/c we need to intialize the map ahead of time which makes it impossible to set the varyign origins
class EnemyConstructor {
	std::map < std::string, std::unique_ptr <Enemy>(*) (const Coordinate &, const char)> enemyMap;

	template <typename T> std::unique_ptr <Enemy> createEnemyInstance(const Coordinate & origin, const char tile) {
		return std::make_unique <T>(origin, tile);
	}

public:
	EnemyConstructor(void) {
		enemyMap.emplace("Tal'Doon Cultist", &createEnemyInstance)
	}
};
