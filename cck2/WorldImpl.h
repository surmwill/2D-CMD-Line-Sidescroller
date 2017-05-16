#pragma once
#include <memory>
#include "Display.h"

class Level;
class Player;
class Observer;

struct WorldImpl {
	WorldImpl() : display(std::make_unique <Display>()) {};

	std::unique_ptr <Level> level;
	std::unique_ptr <Player> player;
	std::unique_ptr <Observer> display;
};