#pragma once
#include "Level.h"

class Observer;

class LevelOne final: public Level {
public:
	LevelOne(Observer ** const map);
	~LevelOne();
};

