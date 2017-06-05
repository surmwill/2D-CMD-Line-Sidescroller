#pragma once
#include <memory>
#include "Coordinate.h"

class Observer;

class Level {
protected:
	Level(const Coordinate playerStart);

	//every level has a map
	std::shared_ptr <Observer> map; 

	//every level has a position where the player starts at
	const Coordinate playerStart;

public:
	virtual ~Level() = default;
	virtual Coordinate getPlayerStart(void) = 0;
};

