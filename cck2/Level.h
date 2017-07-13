#pragma once
#include <memory>
#include <vector>
#include "Coordinate.h"
#include "Map.h"
#include "Enemy.h"
#include <string>

class Observer;

//add a function check aggro which returns a vector of all enemies aggrod after a players move

class Level {
protected:
	Level(const Coordinate playerStart);

	//every level has a set of enemies
	std::vector <Enemy> enemies;

	//every level has a position where the player starts at
	const Coordinate playerStart;

public:
	virtual ~Level() = default;
	virtual Coordinate getPlayerStart(void) = 0;

	//fills our vector of enemies
	virtual void findEnemies(void) = 0;

	//every level has acess to the same map class
	static std::shared_ptr <Map> map;
};

