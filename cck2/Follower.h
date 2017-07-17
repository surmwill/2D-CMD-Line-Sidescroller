#pragma once
#include "Combatent.h"

class Follower : public Combatent {
public:
	Follower();
	~Follower();

	void followPlayer(void);
};

