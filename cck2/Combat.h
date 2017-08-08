#pragma once
#include <vector>
#include "Follower.h"
#include "Enemy.h"
#include "Dialogue.h"
#include <memory>

class Combatent;

class Combat
{
	std::vector <Combatent *> friendlies;
	std::vector <Combatent *> enemies;
	std::vector <Enemy *> deadEnemies;
	std::vector <Follower *> deadFollowers;

	Combatent * player;

public:
	// Engaging in combat with friendlies on the players side
	Combat(
		std::vector <Combatent *> & friendlies,
		std::vector <Combatent *> & enemies);

	// Engaging in combat with only the player
	Combat(
		Combatent * const player,
		std::vector <Combatent *> & enemies
	);

	void nextStage(void);

	std::vector <Enemy *> reportDeadEnemies(void);
	//std::vector <Follower *> & reportDeadFollowers(void);

	~Combat();
};

