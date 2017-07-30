#pragma once
#include <memory>
#include <string>
#include "Combatent.h"
#include "Coordinate.h"

class Observer;
struct EnemyImpl;
struct Coordinate;

class Enemy : public Combatent {
protected:
	Coordinate position;

	const char tile;

	// distance the enemy will notice you
	const int aggroRange;

	// determines how aggresive the enemy is (high threat means the enemy will attack on site)
	const int threat; 

	Enemy(
		const char tile,
		const int aggroRange,
		const int threat);

public:
	static std::shared_ptr <Observer> map;

	virtual ~Enemy();

	void spawn(const Coordinate & origin);

	/* Overwrites from combatent */
	virtual void moveLeft(void) override;
	virtual void moveRight(void) override;
	virtual void moveUp(void) override;
	virtual void moveDown(void) override;

	virtual void giveDialogue(const std::string & text) override;
	/* End of overwrites from combatent */

	// Enemies will follow a specific patrol path
	virtual void patrol(void);
};

