#pragma once
#include <memory>
#include <vector>
#include "Coordinate.h"
#include "Map.h"
#include "Enemy.h"
#include <string>
#include "EnemyConstructor.h"

class Observer;

//add a function check aggro which returns a vector of all enemies aggrod after a players move

class Level {
protected:
	Level(const Coordinate playerStart);

	//every level has a set of enemies
	std::vector <std::unique_ptr <Enemy>> enemies;

	std::map <const char, std::string> enemyLookup;

	//every level has a position where the player starts at
	const Coordinate playerStart;

	EnemyConstructor enemyConstructor;

public:
	virtual ~Level() = default;
	virtual Coordinate getPlayerStart(void) = 0;

	//fills our vector of enemies
	virtual void findEnemies(void) = 0;

	//every level has acess to the same map class
	static std::unique_ptr <Map> map;

	//enemies will be continually moving around the map
	void moveEnemies(void);

	//returns a vector of enemies who are close enough to the player to want to enagge in combat
	std::vector <Combatent*> enemiesAggrod(const Coordinate & playerPosition);
};

