#pragma once

#include "Coordinate.h"

struct PlayerImpl {
	Coordinate position{ 0 , 0 };
	const char playerTile = '+';
};
