#pragma once

#include "Coordinate.h"

struct Tile final {
	Tile(
		const int tileX,
		const int tileY,
		const char tileDesign
	) : coords{ tileX, tileY }, design{ tileDesign } {};

	char design;
	Coordinate coords;
};