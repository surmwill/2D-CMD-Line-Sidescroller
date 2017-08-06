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
		const Coordinate & origin,
		const char tile,
		const int aggroRange,
		const int threat);

public:
	static Observer * map;

	virtual ~Enemy();

	void spawn(const Coordinate & origin);
	bool aggrod(const Coordinate & playerPosition);

	/* Overwrites from combatent */
	virtual Coordinate & moveLeft(void) override;
	virtual Coordinate & moveRight(void) override;
	virtual Coordinate & moveUp(void) override;
	virtual Coordinate & moveDown(void) override;

	virtual void giveDialogue(const std::string & text) override;
	virtual void takeTurn(void) override = 0;
	/* End of overwrites from combatent */

	// Enemies will follow a specific patrol path
	virtual void patrol(void);
};

