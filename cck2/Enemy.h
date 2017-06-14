#pragma once
#include <memory>
#include "Combatent.h"

class Observer;
struct EnemyImpl;
struct Coordinate;

class Enemy : public Combatent {
	std::unique_ptr <EnemyImpl> enemyImpl;

public:
	static std::shared_ptr <Observer> map;
	inline virtual ~Enemy() = default;

protected:
	Enemy(const Coordinate & origin, const char tile);
};

