#pragma once

#include "Coordinate.h"

struct PlayerImpl {
	PlayerImpl(const Coordinate playerStart) : position(playerStart) {};
	Coordinate position;
	const char playerTile = '+';
};
