#pragma once
#include <memory>
#include "Combatent.h"

class Observer;

class Enemy : public Combatent {
public:
	static std::shared_ptr <Observer> map;
	inline virtual ~Enemy() = default;

protected:
	Enemy() = default;
};

