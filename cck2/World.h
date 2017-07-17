#pragma once
#include <memory>
#include "Player.h"

class Level;
class CmdInterpreter;
struct WorldImpl;

class World final {
public:
	World(CmdInterpreter * const cmd);
	~World();

	World & movePlayer(const int direction);

	// moves enemies, perhaps part of the level moves if it is affected by magic
	void animateWorld(void);

private:
	std::unique_ptr <WorldImpl> worldImpl;
};

