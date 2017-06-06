#pragma once
#include <memory>
#include "Display.h"

class Level;
class Player;
class Observer;
class Combatent;

struct WorldImpl {
	WorldImpl() : display(std::make_unique <Display>()) {};

	std::unique_ptr <Level> level;
	std::unique_ptr <Combatent> playerInCombat;
	std::unique_ptr <Display> display;

	Player * player;
};