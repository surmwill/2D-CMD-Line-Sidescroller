#pragma once
#include <memory>
#include "Player.h"

class Level;
struct WorldImpl;

class World final {
public:
	World();
	~World();
	World & movePlayer(const int direction);

private:
	std::unique_ptr <WorldImpl> worldImpl;
};

