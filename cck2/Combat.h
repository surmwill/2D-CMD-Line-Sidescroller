#pragma once
#include <vector>

class Combatent;

class Combat
{
	std::vector <Combatent *> friendlies;
	std::vector <Combatent *> enemies;
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

	~Combat();
};

