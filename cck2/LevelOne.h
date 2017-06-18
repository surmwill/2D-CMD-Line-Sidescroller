#pragma once
#include "Level.h"
#include "Coordinate.h"
#include "Map.h"
#include <memory>

class Display;
struct LevelOneImpl;

class LevelOne final: public Level {
	std::unique_ptr <LevelOneImpl> levelImpl;

public:
	LevelOne();

	virtual Coordinate getPlayerStart(void);
	virtual void findEnemies(void) override;

	~LevelOne();
};

