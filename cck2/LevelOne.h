#pragma once
#include "Level.h"
#include "Coordinate.h"
#include "Map.h"

class Display;

class LevelOne final: public Level {
public:
	LevelOne();

	virtual Coordinate getPlayerStart(void);

	~LevelOne();
};

