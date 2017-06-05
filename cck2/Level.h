#pragma once
#include <memory>
#include "Coordinate.h"
#include "Map.h"

class Observer;

class Level {
protected:
	Level(const Coordinate playerStart);

	//every level has a position where the player starts at
	const Coordinate playerStart;

public:
	virtual ~Level() = default;
	virtual Coordinate getPlayerStart(void) = 0;

	//every level has a map
	static std::shared_ptr <Map> map;
};

