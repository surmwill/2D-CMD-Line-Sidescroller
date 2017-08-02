#pragma once
#include <memory>
#include "Display.h"

class Level;
class Player;
class Observer;
class Combatent;

struct WorldImpl {
	WorldImpl() {};

	std::unique_ptr <Level> level;
	std::unique_ptr <Display> display;
	std::unique_ptr <Player> player;
};