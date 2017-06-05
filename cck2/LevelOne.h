#pragma once
#include "Level.h"
#include "Coordinate.h"

class Display;

class LevelOne final: public Level {
public:
	LevelOne(
		Observer ** const map, 
		Display * const display);

	virtual Coordinate getPlayerStart(void);

	~LevelOne();
};

