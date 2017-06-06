#pragma once
#include <memory>
#include <vector>
#include "Coordinate.h"
#include "Map.h"
#include "Enemy.h"

class Observer;

class Level {
protected:
	Level(const Coordinate playerStart);

	//every level has a position where the player starts at
	const Coordinate playerStart;

	//every level has a set of enemies
	std::vector <Enemy> enemies;

public:
	virtual ~Level() = default;
	virtual Coordinate getPlayerStart(void) = 0;

	//every level has a map
	static std::shared_ptr <Map> map;
};

