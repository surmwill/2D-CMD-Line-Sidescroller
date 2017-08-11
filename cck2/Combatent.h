#pragma once
#include <string>
#include "Coordinate.h"

class Player;

class Combatent
{
public:
	Combatent();
	~Combatent();

	virtual Coordinate & moveLeft(void) = 0;
	virtual Coordinate & moveRight(void) = 0;
	virtual Coordinate & moveUp(void) = 0;
	virtual Coordinate & moveDown(void) = 0;

	virtual void takeTurn(void) = 0;
	bool isDead(void);
	virtual void giveDialogue(const std::string & text, bool slowType) = 0;
};

