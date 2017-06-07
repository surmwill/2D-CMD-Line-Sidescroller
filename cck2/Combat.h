#pragma once
#include <vector>

class Combatent;

class Combat
{
public:
	Combat(
		std::vector <Combatent *> friendlies,
		std::vector <Combatent *> enemies);

	~Combat();
};

