#pragma once
#include "Coordinate.h"


struct EnemyImpl {
	EnemyImpl(const Coordinate & origin, const char tile) :
	position(origin), 
	tile(tile) {};

	Coordinate position;
	const char tile;
};
