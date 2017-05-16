#pragma once
#include "Level.h"

class Observer;
class Display;

class LevelOne final: public Level {
public:
	LevelOne(Observer ** const map, Observer * const display);
	~LevelOne();
};

