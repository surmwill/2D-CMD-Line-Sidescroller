#pragma once

#include "Coordinate.h"
#include "Milestones.h"
#include "Statistics.h"

struct PlayerImpl {
	PlayerImpl(const Coordinate playerStart) : position(playerStart) {};
	Coordinate position;
	const char playerTile = '+';

	// Used to track the player's progression through the game
	Milestones milestones;

	// Information about the player (attack, health, etc..)
	PlayerStats stats;
};
