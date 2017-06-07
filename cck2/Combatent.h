#pragma once

class Player;

class Combatent
{
public:
	Combatent();
	~Combatent();

	virtual void moveLeft(void) = 0;
	virtual void moveRight(void) = 0;
	virtual void moveUp(void) = 0;
	virtual void moveDown(void) = 0;
};

