#pragma once
#include "Level.h"

class Display;

class LevelOne final: public Level {
public:
	LevelOne(Observer ** const map, Display * const display);
	~LevelOne();
};

