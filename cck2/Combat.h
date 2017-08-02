#pragma once
#include <vector>

class Combatent;

class Combat
{
public:
	// Enaging in combat with friendlies on the players side
	Combat(
		std::vector <Combatent *> friendlies,
		std::vector <Combatent *> enemies);

	// Enagging in combat with only the player
	Combat(
		Combatent * const player,
		std::vector <Combatent *> enemies
	);

	~Combat();
};

