#pragma once
#include <memory>
#include <string>
#include "Combatent.h"

class Observer;
struct EnemyImpl;
struct Coordinate;

class Enemy : public Combatent {
	std::unique_ptr <EnemyImpl> enemyImpl;

public:
	static std::shared_ptr <Observer> map;

	Enemy(const Coordinate & origin, const char tile);
	virtual ~Enemy();

	virtual void moveLeft(void) override;
	virtual void moveRight(void) override;
	virtual void moveUp(void) override;
	virtual void moveDown(void) override;

	virtual void giveDialogue(const std::string & text) override;
};

