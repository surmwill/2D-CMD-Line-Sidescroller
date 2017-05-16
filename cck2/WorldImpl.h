#pragma once
#include <memory>
#include "Display.h"

class Level;
class Player;

struct WorldImpl {
	std::unique_ptr <Level> level;
	std::unique_ptr <Player> player;
	Display display;
};